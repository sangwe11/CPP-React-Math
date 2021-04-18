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
			static const size_t DIAG = std::min(M, N);
			using value_type = T;

			template <typename TT>
			using enable_if_square = typename std::enable_if<M == N, TT>::type;

			template <typename TT>
			using enable_if_reducible = typename std::enable_if<M >= 3 && N >= 3, TT >::type;

			matrix();
			explicit matrix(const T& a);
			explicit matrix(const T(&data)[M * N]);

			template <size_t MM, size_t NN, typename TT>
			matrix(const matrix<MM, NN, TT>& m);

			// Accessors
			inline T& at(const size_t& row_index, const size_t& col_index);
			inline const T& at(const size_t& row_index, const size_t& col_index) const;
			const vector<N, T> row(const size_t& row_index) const;
			const vector<M, T> col(const size_t& col_index) const;

			// Utility functions
			template <typename TT = enable_if_square<T>>
			const T determinant() const;

			template <size_t P>
			const matrix<M, P, T> dot(const matrix<N, P, T>& m) const;

			template <typename TT = enable_if_square<T>>
			const matrix<M, N, T> inverse() const;

			const bool invertible() const;

			const matrix<M, N, T> cofactors() const;

			template <typename TT = enable_if_reducible<T>>
			const matrix<M - 1, N - 1, T> reduce(const size_t &ignore_row, const size_t &ignore_col) const;

			template <size_t MM, size_t NN, typename TT>
			const matrix<MM, NN, TT> sub_matrix(const size_t &row_start, const size_t& col_start) const;

			void set(const T* data, size_t size);
			void set(const T(&data)[M * N]);
			void set_row(const T(&data)[M], const size_t& row);
			void set_col(const T(&data)[N], const size_t& col);

			void set_row(const vector<M>& data, const size_t& row);
			void set_col(const vector<N>& data, const size_t& col);

			matrix<M, N, T>& swap_row(const size_t& row1, const size_t& row2);
			matrix<M, N, T>& swap_col(const size_t& col1, const size_t& col2);

			const matrix<N, M, T> transpose() const;

			// Static utility functions
			template <size_t NN, typename TT>
			const static TT determinant(const matrix<NN, NN, TT>& m);

			template <size_t MM, size_t NN, size_t P, typename TT>
			const static matrix<MM, P, TT> dot(const matrix<MM, NN, TT>& a, const matrix<NN, P, TT>& b);

			template <size_t NN, typename TT>
			const static matrix<NN, NN, TT> inverse(const matrix<NN, NN, TT>& m);

			template <size_t MM, size_t NN, typename TT>
			const static matrix<MM, NN, TT> outer_product(const vector<MM, TT>& c, const vector<NN, TT>& r);

			const static matrix<N, M, T> transpose(const matrix<M, N, T> &m);

			// Static instantiator
			//template <typename TT = enable_if_square<T>>
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

			template <size_t P>
			matrix<M, P, T> operator*(const matrix<N, P, T>& m) const;

			vector<M, T> operator*(const vector<N, T>& v) const;

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
			static const matrix<M, N, T> IDENTITY;

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
			for (int i = 0; i < M * N; ++i)
				m_data[i] = a;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>::matrix(const T(&data)[M * N])
		{
			for (int i = 0; i < M * N; ++i)
				m_data[i] = data[i];
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, typename TT>
		matrix<M, N, T>::matrix(const matrix<MM, NN, TT>& m) : m_data()
		{
			size_t min_M = std::min(M, MM);
			size_t min_N = std::min(N, NN);
			
			for (int row_index = 0; row_index < min_M; ++row_index)
				for (int col_index = 0; col_index < min_N; ++col_index)
					this->at(row_index, col_index) = static_cast<T>(m.at(row_index, col_index));
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
		const vector<N, T> matrix<M, N, T>::row(const size_t& row_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(M > row_index);
#endif

			vector<N, T> tmp;

			for (int col_index = 0; col_index < N; ++col_index)
				tmp[col_index] = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const vector<M, T> matrix<M, N, T>::col(const size_t& col_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(N > col_index);
#endif

			vector<M, T> tmp;

			for (int row_index = 0; row_index < M; ++row_index)
				tmp[row_index] = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::swap_row(const size_t& row1, const size_t& row2)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(row1 < M && row2 < M);
#endif	

			for (int i = 0; i < M; ++i)
				std::swap(this->at(row1, i), this->at(row2, i));

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::swap_col(const size_t& col1, const size_t& col2)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(col1 < N && col2 < N);
#endif	

			for (int i = 0; i < N; ++i)
				std::swap(this->at(i, col1), this->at(i, col2));

			return *this;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const T matrix<M, N, T>::determinant() const
		{
			matrix<N, M, T> matrix = *this;

			T det = static_cast<T>(1);

			for (int i = 0; i < N; ++i)
			{
				T pivotElement = matrix.at(i, i);
				int pivotRow = i;

				for (int row = i + 1; row < M; ++row)
				{
					if (fabs(matrix.at(row, i)) > fabs(pivotElement))
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

				if (fabs(pivotElement) < std::numeric_limits<T>::epsilon() * static_cast<T>(this->DIAG))
					return static_cast<T>(0);

				det *= pivotElement;

				for (int row = i + 1; row < M; ++row)
				{
					for (int col = i + 1; col < N; ++col)
					{
						matrix.at(row, col) -= (matrix.at(row, i) / pivotElement) * matrix.at(i, col);
					}
				}
			}

			if (fabs(det) < std::numeric_limits<T>::epsilon() * static_cast<T>(this->DIAG))
				return static_cast<T>(0);

			return det;
		}

		template <size_t M, size_t N, typename T>
		template <size_t P>
		const matrix<M, P, T> matrix<M, N, T>::dot(const matrix<N, P, T>& m) const
		{
			matrix<M, P, T> tmp;

			for (int i = 0; i < M; ++i)
				for(int j = 0; j < P; ++j)
					for(int k = 0; k < N; ++k)
						tmp.at(i, j) += this->at(i, k) * m.at(k, j);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const matrix<M, N, T> matrix<M, N, T>::inverse() const
		{
			if (!invertible())
				return matrix<M, N, T>::ZERO;

			matrix<M, N, T> tmp = this->cofactors(); // co-factors
			tmp = tmp.transpose(); // adjugate

			T det = this->determinant(); // determinant

			tmp *= static_cast<T>(1) / det; // inverse

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const bool matrix<M, N, T>::invertible() const
		{
			if (M != N)
				return false;

			if (fabs(determinant()) <= 0)
				return false;

			return true;
		}

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::cofactors() const
		{
			matrix<M, N, T> tmp = matrix<M, N, T>::ZERO;

			const size_t negate = 1u;

			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if((i + j) & negate)
						tmp.at(i, j) = -this->reduce(i, j).determinant();
					else
						tmp.at(i, j) = this->reduce(i, j).determinant();
				}
			}

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
		void matrix<M, N, T>::set(const T* data, size_t size)
		{
			size_t len = std::min(size, M * N);
			std::memcpy(m_data, data, len * sizeof(T));
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set(const T(&data)[M * N])
		{
			std::memcpy(m_data, data, M * N * sizeof(T));
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_row(const T(&data)[M], const size_t& row)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(row < N);
#endif	

			for (int i = 0; i < M; ++i)
				this->at(row, i) = data[i];
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_col(const T(&data)[N], const size_t& col)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(col < M);
#endif	

			for (int i = 0; i < N; ++i)
				this->at(i, col) = data[i];
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_row(const vector<M>& data, const size_t& row)
		{
			this->set_row(data.m_data, row);
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_col(const vector<N>& data, const size_t& col)
		{
			this->set_col(data.m_data, col);
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
		template <size_t NN, typename TT>
		const static TT matrix<M, N, T>::determinant(const matrix<NN, NN, TT>& m)
		{
			return m.determinant();
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, size_t P, typename TT>
		const static matrix<MM, P, TT> matrix<M, N, T>::dot(const matrix<MM, NN, TT>& a, const matrix<NN, P, TT>& b)
		{
			return a.dot(b);
		}

		template <size_t M, size_t N, typename T>
		template <size_t NN, typename TT>
		const static matrix<NN, NN, TT> matrix<M, N, T>::inverse(const matrix<NN, NN, TT>& m)
		{
			return m.inverse();
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, typename TT>
		const static matrix<MM, NN, TT> matrix<M, N, T>::outer_product(const vector<MM, TT>& c, const vector<NN, TT>& r)
		{
			matrix<MM, NN, TT> tmp;

			for (int i = 0; i < MM; ++i)
				for (int j = 0; j < NN; ++j)
					tmp.at(i, j) = c[i] * r[j];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const static matrix<N, M, T> matrix<M, N, T>::transpose(const matrix<M, N, T>& m)
		{
			return m.transpose();
		}

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::get_identity()
		{
			matrix<M, N, T> tmp;

			for (int i = 0; i < tmp.DIAG; ++i)
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

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator--()
		{
			for (int i = 0; i < M * N; ++i)
				--m_data[i];

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator*=(const T& c)
		{
			for (int i = 0; i < M * N; ++i)
				m_data[i] *= c;

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator/=(const T& c)
		{
			for (int i = 0; i < M * N; ++i)
				m_data[i] /= c;

			return *this;
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
		template <size_t P>
		matrix<M, P, T> matrix<M, N, T>::operator*(const matrix<N, P, T>& m) const
		{
			return this->dot(m);
		}

		template <size_t M, size_t N, typename T>
		vector<M, T> matrix<M, N, T>::operator*(const vector<N, T>& v) const
		{
			vector<M, T> tmp;

			for (int i = 0; i < M; ++i)
				for (int j = 0; j < N; ++j)
					tmp[i] += this->at(i, j) * v[j];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		vector<N, T> operator*(const vector<M, T>& v, const matrix<M, N, T>& m)
		{
			vector<N, T> tmp;

			for (int i = 0; i < M; ++i)
				for (int j = 0; j < N; ++j)
					tmp[j] += m.at(i, j) * v[i];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::ZERO(0);

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::ONE(1);

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T>  matrix<M, N, T>::IDENTITY(matrix<M, N, T>::get_identity());
	}
}

#endif