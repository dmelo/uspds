g++-4.1 -O3 -march=i686 -mtune=pentium4 -msse ./src/simulator/simulator.cc ./bin/campo.o ./bin/bola.o ./bin/robo.o ./bin/objeto.o ./bin/vetor2d.o ./bin/protocolo.o -o ./bin/simulator -lpthread
./src/simulator/simulator.cc: In function ‘void* executar_movimento(void*)’:
./src/simulator/simulator.cc:120: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:120: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:122: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:122: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:154: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:154: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:166: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:166: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:168: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:168: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:170: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:170: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc: In function ‘void* eyes_sender(void*)’:
./src/simulator/simulator.cc:504: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
./src/simulator/simulator.cc:504: error: reference to ‘count’ is ambiguous
./src/simulator/simulator.cc:24: error: candidates are: int count
/usr/lib/gcc/i486-linux-gnu/4.1.2/../../../../include/c++/4.1.2/bits/stl_algo.h:413: error:                 template<class _InputIterator, class _Tp> typename std::iterator_traits::difference_type std::count(_InputIterator, _InputIterator, const _Tp&)
make: *** [bin/simulator] Error 1
