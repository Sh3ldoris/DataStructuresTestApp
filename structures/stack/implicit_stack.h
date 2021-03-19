#pragma once

#include "stack.h"
#include "../list/array_list.h"

namespace structures
{
	/// <summary> Implicitny zasobn�k. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zasobniku. </typepram>
	template<typename T>
	class ImplicitStack : public Stack<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ImplicitStack();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Implicitny zasobn�k, z ktoreho sa prevezmu vlastnosti. </param>
		ImplicitStack(const ImplicitStack<T>& other);

		/// <summary> Destruktor. </summary>
		~ImplicitStack();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zasobnika. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zasobniku. </summary>
		/// <returns> Pocet prvkov v zasobniku. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zasobnik, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
		Stack<T>& operator=(const Stack<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zasobnik, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
		ImplicitStack<T>& operator=(const ImplicitStack<T>& other);

		/// <summary> Vymaze zasobnik. </summary>
		void clear() override;

		/// <summary> Prida prvok do zasobnika. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void push(const T& data) override;

		/// <summary> Odstrani prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati prvok na vrchole zasobnika. </summary>
		/// <returns> Prvok na vrchole zasobnika. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>  
		const T peek() const override;

	protected:
		/// <summary> Zoznam, pomocou ktoreho je implementovany zasobnik. </summary>
		ArrayList<T>* list_;
	};

	template<typename T>
	ImplicitStack<T>::ImplicitStack() :
		Stack(),
		list_(new ArrayList<T>())
	{
	}

	template<typename T>
	ImplicitStack<T>::ImplicitStack(const ImplicitStack<T>& other) :
		ImplicitStack()
	{
		*this = other;
	}

	template<typename T>
	ImplicitStack<T>::~ImplicitStack()
	{
		//TODO 05: ImplicitStack
	}

	template<typename T>
	inline Stack<T>& ImplicitStack<T>::operator=(const Stack<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ImplicitStack<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ImplicitStack<T>& ImplicitStack<T>::operator=(const ImplicitStack<T>& other)
	{
		//TODO 05: ImplicitStack
		throw std::exception("ImplicitStack<T>::operator=: Not implemented yet.");
	}

	template<typename T>
	inline Structure * ImplicitStack<T>::clone() const
	{
		return new ImplicitStack<T>(*this);
	}

	template<typename T>
	size_t ImplicitStack<T>::size() const
	{
		//TODO 05: ImplicitStack
		throw std::exception("ImplicitStack<T>::size: Not implemented yet.");
	}

	template<typename T>
	inline void ImplicitStack<T>::clear()
	{
		//TODO 05: ImplicitStack
		throw std::exception("ImplicitStack<T>::clear: Not implemented yet.");
	}

	template<typename T>
	inline void ImplicitStack<T>::push(const T& data)
	{
		//TODO 05: ImplicitStack
		throw std::exception("ImplicitStack<T>::push: Not implemented yet.");
	}

	template<typename T>
	inline T ImplicitStack<T>::pop()
	{
		//TODO 05: ImplicitStack
		throw std::exception("ImplicitStack<T>::pop: Not implemented yet.");
	}

	template<typename T>
	inline T& ImplicitStack<T>::peek()
	{
		//TODO 05: ImplicitStack
		throw std::exception("ImplicitStack<T>::peek: Not implemented yet.");
	}

	template<typename T>
	inline const T ImplicitStack<T>::peek() const
	{
		//TODO 05: ImplicitStack
		throw std::exception("ImplicitStack<T>::peek: Not implemented yet.");
	}
}