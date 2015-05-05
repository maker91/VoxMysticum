#pragma once

#include <memory>
#include <string>
#include <map>

template <typename Key, typename Base>
class TypeFactory
{
public:
	template <typename Derived, typename... Args>
	static void registerType(Key id)
	{
		Product<Args...>::products[id] = std::make_shared<Product<Args...>::BluePrint<Derived>>();
	}

	template <typename... Args>
	static std::shared_ptr<Base> create(Key id, Args... args)
	{
		if (!Product<Args...>::products.count(id))
			return std::shared_ptr<Base>();
		return Product<Args...>::products[id]->create(args...);
	}

private:
	template <typename... Args>
	struct Product
	{
		struct IBluePrint
		{
			virtual std::shared_ptr<Base> create(Args...) = 0;
		};

		template <typename Derived>
		struct BluePrint : public IBluePrint
		{
			std::shared_ptr<Base> create(Args... args)
			{
				return std::make_shared<Derived>(args...);
			}
		};

		static std::map<Key, std::shared_ptr<IBluePrint>> products;
	};
};

template <typename Key, typename Base>
template <typename... Args>
std::map<Key, std::shared_ptr<typename TypeFactory<Key, Base>::Product<Args...>::IBluePrint>> TypeFactory<Key, Base>::Product<Args...>::products;