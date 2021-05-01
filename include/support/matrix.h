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
			typename check_type_arithmetic<T>::type ct{};

		public:
			static const size_t ROWS = N;
			static const size_t COLS = M;
			static const size_t DIAG = std::min(ROWS, COLS);

			using value_type = T;
			typedef vector<ROWS, T> row_type;
			typedef vector<COLS, T> col_type;

			template <typename TT>
			using enable_if_square = typename std::enable_if<ROWS == COLS, TT>;

			template <typename TT>
			using enable_if_reducible = typename std::enable_if<ROWS >= 3 && COLS >= 3, TT>;

			matrix();
			explicit matrix(const T& a);
			explicit matrix(const T(&data)[ROWS * COLS]);

			template <size_t MM, size_t NN, typename TT>
			explicit matrix(const matrix<MM, NN, TT>& m);

			// Accessors
			inline T& at(const size_t& row_index, const size_t& col_index);
			inline const T& at(const size_t& row_index, const size_t& col_index) const;
			const vector<matrix<M, N, T>::COLS, T> row(const size_t& row_index) const;
			const vector<matrix<M, N, T>::ROWS, T> col(const size_t& col_index) const;

			// Utility functions
			template <typename TT = enable_if_square<T>>
			const T determinant() const;

			template <size_t P>
			const matrix<P, N, T> dot(const matrix<P, M, T>& m) const;

			template <typename TT = enable_if_square<T>>
			const matrix<M, N, T> inverse() const;

			const bool invertible() const;

			template <typename TT = enable_if_square<T>>
			const matrix<M, N, T> cofactors() const;

			template <typename TT = enable_if_reducible<T>>
			const matrix<M - 1, N - 1, T> reduce(const size_t &ignore_row, const size_t &ignore_col) const;

			template <size_t MM, size_t NN, typename TT>
			const matrix<MM, NN, TT> sub_matrix(const size_t &row_start, const size_t& col_start) const;

			void set(const T* data, size_t size);
			void set(const T(&data)[matrix<M, N, T>::ROWS * matrix<M, N, T>::COLS]);
			void set_row(const T(&data)[matrix<M, N, T>::COLS], const size_t& row);
			void set_col(const T(&data)[matrix<M, N, T>::ROWS], const size_t& col);

			void set_row(const vector<matrix<M, N, T>::COLS, T>& data, const size_t& row);
			void set_col(const vector<matrix<M, N, T>::ROWS, T>& data, const size_t& col);

			matrix<M, N, T>& swap_row(const size_t& row1, const size_t& row2);
			matrix<M, N, T>& swap_col(const size_t& col1, const size_t& col2);

			const matrix<N, M, T> transpose() const;

			// Static utility functions
			template <size_t NN, typename TT>
			const static matrix<NN, NN, TT> cofactors(const matrix<NN, NN, TT>& m);

			template <size_t NN, typename TT>
			const static TT determinant(const matrix<NN, NN, TT>& m);

			template <size_t MM, size_t NN, size_t PP, typename TT>
			const static matrix<PP, NN, TT> dot(const matrix<MM, NN, TT>& a, const matrix<PP, MM, TT>& b);

			template <size_t NN, typename TT>
			const static matrix<NN, NN, TT> inverse(const matrix<NN, NN, TT>& m);

			template <size_t MM, size_t NN, typename TT>
			const static matrix<NN, MM, TT> outer_product(const vector<MM, TT>& c, const vector<NN, TT>& r);

			const static matrix<N, M, T> transpose(const matrix<M, N, T> &m);

			// Operators
			inline T& operator()(const size_t& row_index, const size_t& col_index);
			inline const T& operator()(const size_t& row_index, const size_t& col_index) const;

			template <size_t MM, size_t NN, typename TT>
			const bool operator==(const matrix<MM, NN, TT>& m) const;

			template <size_t MM, size_t NN, typename TT>
			const bool operator!=(const matrix<MM, NN, TT>& m) const;

			matrix<M, N, T>& operator++();
			matrix<M, N, T>& operator--();

			matrix<M, N, T>& operator*=(const T& c);
			matrix<M, N, T>& operator/=(const T& c);
			matrix<M, N, T>& operator+=(const T& c);
			matrix<M, N, T>& operator-=(const T& c);

			matrix<M, N, T> operator*(const T& c) const;
			matrix<M, N, T> operator/(const T& c) const;
			matrix<M, N, T> operator+(const T& c) const;
			matrix<M, N, T> operator-(const T& c) const;

			matrix<M, N, T> operator+(const matrix<M, N, T>& m) const;
			matrix<M, N, T> operator-(const matrix<M, N, T>& m) const;

			template <size_t P>
			matrix<P, N, T> operator*(const matrix<P, M, T>& m) const;

			template <size_t P>
			matrix<P, N, T> operator/(const matrix<P, M, T>& m) const;

			friend std::ostream& operator<<(std::ostream& out, const matrix<M, N, T>& m)
			{
				out << "Mat" << m.COLS << "x" << m.ROWS << ":\n";

				for (int row_index = 0; row_index < m.ROWS; ++row_index)
				{
					for (int col_index = 0; col_index < m.COLS; ++col_index)
						out << m(row_index, col_index) << ' ';

					if(row_index != m.ROWS - 1)
						out << '\n';
				}

				return out;
			}

			// General mat defaults
			static const matrix<M, N, T> ZERO;
			static const matrix<M, N, T> ONE;
			static const matrix<M, N, T> IDENTITY;

		public:
			T m_data[ROWS * COLS];
		};

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>::matrix() : m_data()
		{
			for (int i = 0; i < DIAG; ++i)
				this->at(i, i) = static_cast<T>(1);
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>::matrix(const T& a)
		{
			for (int i = 0; i < M * N; ++i)
				m_data[i] = a;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>::matrix(const T(&data)[ROWS * COLS])
		{
			for (int i = 0; i < M * N; ++i)
				m_data[i] = data[i];
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, typename TT>
		matrix<M, N, T>::matrix(const matrix<MM, NN, TT>& m) : m_data()
		{
			for (int i = 0; i < DIAG; ++i)
				this->at(i, i) = static_cast<T>(1);

			size_t min_ROWS = std::min(ROWS, m.ROWS);
			size_t min_COLS = std::min(COLS, m.COLS);
			
			for (int row_index = 0; row_index < min_ROWS; ++row_index)
				for (int col_index = 0; col_index < min_COLS; ++col_index)
					this->at(row_index, col_index) = static_cast<T>(m.at(row_index, col_index));
		}

		template <size_t M, size_t N, typename T>
		inline T& matrix<M, N, T>::at(const size_t& row_index, const size_t& col_index)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(ROWS > row_index && COLS > col_index);
#endif
			return m_data[row_index + ROWS * col_index];
		}

		template <size_t M, size_t N, typename T>
		inline const T& matrix<M, N, T>::at(const size_t& row_index, const size_t& col_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(ROWS > row_index && COLS > col_index);
#endif
			return m_data[row_index + ROWS * col_index];
		}

		template <size_t M, size_t N, typename T>
		const vector<matrix<M, N, T>::COLS, T> matrix<M, N, T>::row(const size_t& row_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(COLS > row_index);
#endif

			vector<COLS, T> tmp;

			for (int col_index = 0; col_index < COLS; ++col_index)
				tmp[col_index] = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const vector<matrix<M, N, T>::ROWS, T> matrix<M, N, T>::col(const size_t& col_index) const
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(ROWS > col_index);
#endif

			vector<ROWS, T> tmp;

			for (int row_index = 0; row_index < ROWS; ++row_index)
				tmp[row_index] = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::swap_row(const size_t& row1, const size_t& row2)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(row1 < ROWS && row2 < ROWS);
#endif	

			for (int i = 0; i < COLS; ++i)
				std::swap(this->at(row1, i), this->at(row2, i));

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::swap_col(const size_t& col1, const size_t& col2)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(col1 < COLS && col2 < COLS);
#endif	

			for (int i = 0; i < ROWS; ++i)
				std::swap(this->at(i, col1), this->at(i, col2));

			return *this;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const T matrix<M, N, T>::determinant() const
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'determinant' only accepts floating-point inputs");

			matrix<N, M, T> matrix = *this;

			T det = static_cast<T>(1);

			for (int i = 0; i < COLS; ++i)
			{
				T pivotElement = matrix.at(i, i);
				int pivotRow = i;

				for (int row = i + 1; row < ROWS; ++row)
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

				for (int row = i + 1; row < ROWS; ++row)
				{
					for (int col = i + 1; col < COLS; ++col)
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
		const matrix<P, N, T> matrix<M, N, T>::dot(const matrix<P, M, T>& m) const
		{
			matrix<P, N, T> tmp(0);

			for (int i = 0; i < tmp.COLS; ++i)
				for (int j = 0; j < tmp.ROWS; ++j)
					for (int k = 0; k < COLS; ++k)
						tmp.at(j, i) += this->at(j, k) * m.at(k, i);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const matrix<M, N, T> matrix<M, N, T>::inverse() const
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'inverse' only accepts floating-point inputs");

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
			if (ROWS != COLS)
				return false;

			if (fabs(determinant()) <= 0)
				return false;

			return true;
		}

		template <size_t M, size_t N, typename T>
		template <typename TT>
		const matrix<M, N, T> matrix<M, N, T>::cofactors() const
		{
			matrix<M, N, T> tmp = matrix<M, N, T>::ZERO;

			const size_t negate = 1u;

			for (int i = 0; i < ROWS; ++i)
			{
				for (int j = 0; j < COLS; ++j)
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

			for (int i = 0; i < ROWS; ++i)
			{
				int subj = 0;

				if (i == ignore_row)
					continue;

				for (int j = 0; j < COLS; ++j)
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
			matrix<MM, NN, TT> tmp;

#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(ROWS >= row_start + tmp.ROWS && COLS >= col_start + tmp.COLS);
#endif

			for (int row_index = 0; row_index < tmp.ROWS; ++row_index)
				for (int col_index = 0; col_index < tmp.COLS; ++col_index)
					tmp.at(row_index, col_index) = this->at(row_index + row_start, col_index + col_start);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set(const T* data, size_t size)
		{
			size_t len = std::min(size, ROWS * COLS);
			std::memcpy(m_data, data, len * sizeof(T));
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set(const T(&data)[matrix<M, N, T>::ROWS * matrix<M, N, T>::COLS])
		{
			std::memcpy(m_data, data, ROWS * COLS * sizeof(T));
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_row(const T(&data)[matrix<M, N, T>::COLS], const size_t& row)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(row < ROWS);
#endif	

			for (int i = 0; i < COLS; ++i)
				this->at(row, i) = data[i];
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_col(const T(&data)[matrix<M, N, T>::ROWS], const size_t& col)
		{
#ifndef _REACT_NO_SAFE_ACCESSORS
			assert(col < COLS);
#endif	

			for (int i = 0; i < ROWS; ++i)
				this->at(i, col) = data[i];
		}



		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_row(const vector<matrix<M, N, T>::COLS, T>& data, const size_t& row)
		{
			this->set_row(data.m_data, row);
		}

		template <size_t M, size_t N, typename T>
		void matrix<M, N, T>::set_col(const vector<matrix<M, N, T>::ROWS, T>& data, const size_t& col)
		{
			this->set_col(data.m_data, col);
		}

		template <size_t M, size_t N, typename T>
		const matrix<N, M, T> matrix<M, N, T>::transpose() const
		{
			matrix<N, M, T> tmp;

			for (int row_index = 0; row_index < ROWS; ++row_index)
				for (int col_index = 0; col_index < COLS; ++col_index)
					tmp.at(col_index, row_index) = at(row_index, col_index);

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		template <size_t NN, typename TT>
		const matrix<NN, NN, TT> matrix<M, N, T>::cofactors(const matrix<NN, NN, TT>& m)
		{
			return m.cofactors();
		}

		template <size_t M, size_t N, typename T>
		template <size_t NN, typename TT>
		const TT matrix<M, N, T>::determinant(const matrix<NN, NN, TT>& m)
		{
			return m.determinant();
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, size_t PP, typename TT>
		const matrix<PP, NN, TT> matrix<M, N, T>::dot(const matrix<MM, NN, TT>& a, const matrix<PP, MM, TT>& b)
		{
			return a.dot(b);
		}

		template <size_t M, size_t N, typename T>
		template <size_t NN, typename TT>
		const matrix<NN, NN, TT> matrix<M, N, T>::inverse(const matrix<NN, NN, TT>& m)
		{
			return m.inverse();
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, typename TT>
		const matrix<NN, MM, TT> matrix<M, N, T>::outer_product(const vector<MM, TT>& c, const vector<NN, TT>& r)
		{
			matrix<NN, MM, TT> tmp;

			for (int row = 0; row < tmp.ROWS; ++row)
				for (int col = 0; col < tmp.COLS; ++col)
					tmp.at(row, col) = c[row] * r[col];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const matrix<N, M, T> matrix<M, N, T>::transpose(const matrix<M, N, T>& m)
		{
			return m.transpose();
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
		template <size_t MM, size_t NN, typename TT>
		const bool matrix<M, N, T>::operator==(const matrix<MM, NN, TT>& m) const
		{
			if (typeid(T) != typeid(TT))
				return false;

			if (ROWS != m.ROWS || COLS != m.COLS)
				return false;

#ifndef _REACT_EXACT_COMPARISON
			for (int i = 0; i < ROWS * COLS; ++i)
				if (fabs(m_data[i] - m.m_data[i]) > std::numeric_limits<T>::epsilon())
					return false;

			return true;
#else
			return std::memcmp(m_data, m.m_data, sizeof(m_data)) == 0;
#endif
		}

		template <size_t M, size_t N, typename T>
		template <size_t MM, size_t NN, typename TT>
		const bool matrix<M, N, T>::operator!=(const matrix<MM, NN, TT>& m) const
		{
			return !(*this == m);
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator++()
		{
			for (int i = 0; i < ROWS * COLS; ++i)
				++m_data[i];

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator--()
		{
			for (int i = 0; i < ROWS * COLS; ++i)
				--m_data[i];

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator*=(const T& c)
		{
			for (int i = 0; i < ROWS * COLS; ++i)
				m_data[i] *= c;

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator/=(const T& c)
		{
			for (int i = 0; i < ROWS * COLS; ++i)
				m_data[i] /= c;

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator+=(const T& c)
		{
			for (int i = 0; i < ROWS * COLS; ++i)
				m_data[i] += c;

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T>& matrix<M, N, T>::operator-=(const T& c)
		{
			for (int i = 0; i < ROWS * COLS; ++i)
				m_data[i] -= c;

			return *this;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator*(const T& c) const
		{
			matrix<M, N, T> tmp(*this);

			tmp *= c;

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator/(const T& c) const
		{
			matrix<M, N, T> tmp(*this);

			tmp /= c;

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator+(const T& c) const
		{
			matrix<M, N, T> tmp(*this);

			tmp += c;

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator-(const T& c) const
		{
			matrix<M, N, T> tmp(*this);

			tmp -= c;

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator+(const matrix<M, N, T>& m) const
		{
			matrix<M, N, T> tmp(*this);

			for (int i = 0; i < ROWS * COLS; ++i)
				tmp.m_data[i] += m.m_data[i];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> matrix<M, N, T>::operator-(const matrix<M, N, T>& m) const
		{
			matrix<M, N, T> tmp(*this);

			for (int i = 0; i < ROWS * COLS; ++i)
				tmp.m_data[i] -= m.m_data[i];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		template <size_t P>
		matrix<P, N, T> matrix<M, N, T>::operator*(const matrix<P, M, T>& m) const
		{
			return this->dot(m);
		}

		template <size_t M, size_t N, typename T>
		template <size_t P>
		matrix<P, N, T> matrix<M, N, T>::operator/(const matrix<P, M, T>& m) const
		{
			return this->dot(m.inverse());
		}

		template <size_t M, size_t N, typename T>
		typename matrix<M, N, T>::row_type operator*(const matrix<M, N, T>& m, const typename matrix<M, N, T>::col_type& v)
		{
			typename matrix<M, N, T>::row_type tmp;

			for (int i = 0; i < matrix<M, N, T>::ROWS; ++i)
				for (int j = 0; j < matrix<M, N, T>::COLS; ++j)
					tmp[i] += m.at(i, j) * v[j];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		typename matrix<M, N, T>::row_type operator*(const matrix<M, N, T>& m, const typename matrix<M, N, T>::row_type& v)
		{
			typename matrix<M, N, T>::row_type tmp;

			for (int i = 0; i < matrix<M, N, T>::ROWS; ++i)
				for (int j = 0; j < matrix<M, N, T>::COLS; ++j)
					tmp[i] += m.at(i, j) * v[i];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		typename matrix<M, N, T>::col_type operator*(const typename matrix<M, N, T>::col_type& v, const matrix<M, N, T>& m)
		{
			typename matrix<M, N, T>::col_type tmp;

			for (int i = 0; i < matrix<M, N, T>::ROWS; ++i)
				for (int j = 0; j < matrix<M, N, T>::COLS; ++j)
					tmp[j] += m.at(i, j) * v[j];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		typename matrix<M, N, T>::col_type operator*(const typename matrix<M, N, T>::row_type& v, const matrix<M, N, T>& m)
		{
			typename matrix<M, N, T>::col_type tmp;

			for (int i = 0; i < matrix<M, N, T>::ROWS; ++i)
				for (int j = 0; j < matrix<M, N, T>::COLS; ++j)
					tmp[j] += m.at(i, j) * v[i];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> operator*(const T& c, const matrix<M, N, T>& m)
		{
			return m * c;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> operator/(const T& c, const matrix<M, N, T>& m)
		{
			matrix<M, N, T> tmp(m);

			for (int i = 0; i < m.ROWS * m.COLS; ++i)
				tmp.m_data[i] = c / tmp.m_data[i];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> operator+(const T& c, const matrix<M, N, T>& m)
		{
			return m + c;
		}

		template <size_t M, size_t N, typename T>
		matrix<M, N, T> operator-(const T& c, const matrix<M, N, T>& m)
		{
			matrix<M, N, T> tmp(m);

			for (int i = 0; i < m.ROWS * m.COLS; ++i)
				tmp.m_data[i] = c - tmp.m_data[i];

			return tmp;
		}

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::ZERO(0);

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T> matrix<M, N, T>::ONE(1);

		template <size_t M, size_t N, typename T>
		const matrix<M, N, T>  matrix<M, N, T>::IDENTITY;
	}
}

#endif