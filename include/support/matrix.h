#ifndef _RM_MATRIX_H
#define _RM_MATRIX_H

#include "vector.h"

namespace react
{
	namespace support
	{
		template <size_t M, size_t N, typename T = float>
		class matrix
		{
		private:
			typename check_mat_dimension<T, M, N>::type cd{};
			typename check_type<T>::type ct{};

		public:
			static const size_t ROWS = M;
			static const size_t COLS = N;
			using value_type = T;

			template <typename TT>
			using enable_if_square = typename std::enable_if<M == N, TT>::type;

			template <typename TT>
			using enable_if_reducible = typename std::enable_if<M >= 3 && N >= 3, TT >::type;

			matrix();
			explicit matrix(const T& a);

			template <size_t MM, size_t NN, typename TT>
			matrix(const matrix<MM, NN, TT>& m);

			// Accessors
			inline T& at(const size_t& row_index, const size_t& col_index);
			inline const T& at(const size_t& row_index, const size_t& col_index) const;
			const vector<M, T> row(const size_t& row_index) const;
			const vector<N, T> col(const size_t& col_index) const;

			// Utility functions
			const matrix<N, M, T> transpose() const;

			template <typename TT = enable_if_square<T>>
			const matrix<M, N, T> inverse() const;

			const bool invertible() const;

			template <size_t MM, size_t NN, typename TT>
			const matrix<MM, NN, TT> sub_matrix(const size_t &row_start, const size_t& col_start) const;

			template <typename TT = enable_if_reducible<T>>
			const matrix<M - 1, N - 1, T> reduce(const size_t &ignore_row, const size_t &ignore_col) const;

			void set(T* data, size_t size);

			matrix<M, N, T>& swap_row(const size_t& row1, const size_t& row2);
			matrix<M, N, T>& swap_col(const size_t& col1, const size_t& col2);

			// Static utility functions
			const static matrix<N, M, T> transpose(const matrix<M, N, T> &m);

			template <size_t NN, typename TT>
			const static TT determinant(const matrix<NN, NN, TT>& m);

			// Static instantiator
			template <typename TT = enable_if_square<T>>
			static const matrix<M, N, T> get_identity();

			// Operators
			inline T& operator()(const size_t& row_index, const size_t& col_index);
			inline const T& operator()(const size_t& row_index, const size_t& col_index) const;

			const bool operator==(const matrix<M, N, T>& m) const;
			const bool operator!=(const matrix<M, N, T>& m) const;

			matrix<M, N, T>& operator++();
			matrix<M, N, T>& operator--();

			matrix<M, N, T>& operator*=(const T& c);
			matrix<M, N, T>& operator/=(const T& c);

			matrix<M, N, T> operator*(const T& c) const;
			matrix<M, N, T> operator/(const T& c) const;

			friend std::ostream& operator<<(std::ostream& out, const matrix<M, N, T>& m)
			{
				for (int row_index = 0; row_index < M; ++row_index)
				{
					for (int col_index = 0; col_index < N; ++col_index)
						out << m(row_index, col_index) << ' ';

					out << '\n';
				}

				return out;
			}

			// General mat defaults
			static const matrix<M, N, T> ZERO;
			static const matrix<M, N, T> ONE;

		public:
			T m_data[M * N];
		};

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>::matrix() : m_data()
		{
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>::matrix(const T& a)
		{
			for (int i = 0; i < M * M; ++i)
				m_data[i] = a;
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, typename TT>
		matrix<M, N, T>::matrix(const matrix<MM, NN, TT>& m) : m_data()
		{
			size_t min_M = std::min(M, MM);
			size_t min_N = std::min(N, NN);
			
			for (int row_index = 0; row_index < min_M; ++row_index)
				for (int col_index = 0; col_index < min_N; ++col_index)
					this->at(row_index, col_index) = m.at(row_index, col_index);
		}

		template <size_t M, size_t N, typename T>
		inline T& matrix<M, N, T>::at(const size_t& row_index, const size_t& col_index)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(M > row_index && N > col_index);
#endif
			return m_data[col_index * M + row_index];
		}

		template <size_t M, size_t N, typename T>
		inline const T& matrix<M, N, T>::at(const size_t& row_index, const size_t& col_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(M > row_index && N > col_index);
#endif
			return m_data[col_index * M + row_index];
		}

		template <size_t M, size_t N, typename T>
		const vector<M, T> matrix<M, N, T>::row(const size_t& row_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(M > row_index);
#endif

			vector<N, T> tmp;

			for (int col_index = 0; col_index < N; ++col_index)
				tmp[i] = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const vector<N, T> matrix<M, N, T>::col(const size_t& col_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(N > col_index);
#endif

			vector<N, T> tmp;

			for (int row_index = 0; row_index < M; ++row_index)
				tmp[i] = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::swap_row(const size_t& row1, const size_t& row2)
		{
			assert(row1 < M && row2 < M);

			for (int i = 0; i < M; ++i)
				std::swap(this->at(row1, i), this->at(row2, i));

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::swap_col(const size_t& col1, const size_t& col2)
		{
			assert(col1 < N && col2 < N);

			for (int i = 0; i < N; ++i)
				std::swap(this->at(i, col1), this->at(i, col2));

			return *this;
		}

		template <size_t M, size_t N, typename T>
		const matrix<N, M, T> matrix<M, N, T>::transpose() const
		{
			matrix<N, M, T> tmp;

			for (int row_index = 0; row_index < M; ++row_index)
				for (int col_index = 0; col_index < N; ++col_index)
					tmp.at(col_index, row_index) = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const matrix<M, N, T> matrix<M, N, T>::inverse() const
		{
			assert(invertible());

			matrix<M, N * 2, T> tmp(*this);

			// Set right half to identity
			for (int i = 0; i < M; ++i)
				tmp.at(i, N + i) = 1;

			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (i != j)
					{
						T ratio = tmp.at(j, i) / tmp.at(i, i);

						for (int k = 0; k < 2 * N; ++k)
						{
							tmp.at(j, k) = tmp.at(j, k) - ratio * tmp.at(i, k);
						}
					}
				}
			}

			for (int i = 0; i < M; ++i)
			{
				for (int j = N; j < 2 * N; ++j)
				{
					tmp.at(i, j) = tmp.at(i, j) / tmp.at(i, i);
				}
			}

			return tmp.sub_matrix<M, N, T>(0, N);
		}

		template <size_t M, size_t N, typename T>
		const bool matrix<M, N, T>::invertible() const
		{
			if (M != N)
				return false;

			for (int i = 0; i < M; ++i)
				if (at(i, i) == 0)
					return false;

			return true;
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, typename TT>
		const matrix<MM, NN, TT> matrix<M, N, T>::sub_matrix(const size_t& row_start, const size_t& col_start) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(M >= row_start + MM && N >= col_start + NN);
#endif

			matrix<MM, NN, TT> tmp;

			for (int row_index = 0; row_index < MM; ++row_index)
				for (int col_index = 0; col_index < NN; ++col_index)
					tmp.at(row_index, col_index) = this->at(row_index + row_start, col_index + col_start);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const matrix<M - 1, N - 1, T> matrix<M, N, T>::reduce(const size_t& ignore_row, const size_t& ignore_col) const
		{
			matrix<M - 1, N - 1, T> sub_matrix = matrix<M - 1, N - 1, T>::ZERO;

			int subi = 0;

			for (int i = 0; i < M; ++i)
			{	
				int subj = 0;

				if (i == ignore_row)
					continue;

				for (int j = 0; j < N; ++j)
				{
					if (j == ignore_col)
						continue;

					sub_matrix.at(subi, subj) = at(i, j);
					++subj;
				}

				++subi;
			}

			return sub_matrix;
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set(T* data, size_t size)
		{
			size_t len = std::min(size, M * N);
			std::memcpy(m_data, data, len * sizeof(T));
		}

		template <size_t M, size_t N, typename T>
		const static matrix<N, M, T> matrix<M, N, T>::transpose(const matrix<M, N, T>& m)
		{
			return m.transpose();
		}

		template <size_t M, size_t N, typename T>
		template <size_t NN, typename TT>
		const static TT matrix<M, N, T>::determinant(const matrix<NN, NN, TT>& m)
		{
			matrix<NN, NN, TT> matrix = m;

			TT det = static_cast<T>(1);

			for (int i = 0; i < NN; ++i)
			{
				T pivotElement = matrix.at(i, i);
				int pivotRow = i;

				for (int row = i + 1; row < NN; ++row)
				{
					if (std::abs(matrix.at(row, i)) > std::abs(pivotElement))
					{
						pivotElement = matrix.at(row, i);
						pivotRow = row;
					}
				}

				if (pivotElement == static_cast<T>(0))
					return static_cast<T>(0);
				
				if (pivotRow != i)
				{
					matrix.swap_row(i, pivotRow);
					det = -det;
				}

				det *= pivotElement;

				for (int row = i + 1; row < NN; ++row)
				{
					for (int col = i + 1; col < NN; ++col)
					{
						matrix.at(row, col) -= matrix.at(row, i) * matrix.at(i, col) / pivotElement;
					}
				}
			}

			return det;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const matrix<M, N, T> matrix<M, N, T>::get_identity()
		{
			matrix<M, N, T> tmp;

			for (int i = 0; i < tmp.ROWS; ++i)
				tmp.at(i, i) = 1;

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		inline T& matrix<M, N, T>::operator()(const size_t& row_index, const size_t& col_index)
		{
			return at(row_index, col_index);
		}

		template <size_t M, size_t N, typename T>
		inline const T& matrix<M, N, T>::operator()(const size_t& row_index, const size_t& col_index) const
		{
			return at(row_index, col_index);
		}

		template <size_t M, size_t N, typename T>
		const bool matrix<M, N, T>::operator==(const matrix<M, N, T>& m) const
		{
			for (int i = 0; i < M * N; ++i)
				if (m_data[i] != m.m_data[i])
					return false;

			return true;
		}

		template <size_t M, size_t N, typename T>
		const bool matrix<M, N, T>::operator!=(const matrix<M, N, T>& m) const
		{
			return !(*this == m);
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator++()
		{
			for (int i = 0; i < M * N; ++i)
				++m_data[i];
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator--()
		{
			for (int i = 0; i < M * N; ++i)
				--m_data[i];
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator*=(const T& c)
		{
			for (int i = 0; i < M * N; ++i)
				m_data[i] *= c;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator/=(const T& c)
		{
			for (int i = 0; i < M * N; ++i)
				m_data[i] /= c;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator*(const T& c) const
		{
			matrix<M, N, T> tmp;

			for (int i = 0; i < M * N; ++i)
				tmp.m_data[i] *= c;

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator/(const T& c) const
		{
			matrix<M, N, T> tmp;

			for (int i = 0; i < M * N; ++i)
				tmp.m_data[i] /= c;

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::ZERO(0);

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::ONE(1);
	}
}

#endif