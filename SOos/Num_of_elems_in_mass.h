


template<typename T, size_t N>
size_t len(T(&)[N]) 
{
	return N;
}

template<typename T>
auto len(T const& t) -> decltype((void)(t.size()), T::size_type())
{
	return t.size();
}

template<typename T>
size_t len(...)
{
	return 0;
}