#ifndef SLOT_HPP
#define SLOT_HPP

#include <cassert>
#include <vector>

template <class ...Args>
class EventHandler
{
public:
	virtual ~EventHandler() {};
	virtual void call(Args... args) = 0;

protected:
	EventHandler() {};
};

template <class Object, class ...Args>
class MethodHandler : public EventHandler<Args...>
{	
using Method = void (Object::*) (Args...);

public:
	MethodHandler(Object& object, Method method):
		EventHandler<Args...>(),
		m_object(object),
		m_method(method)
	{
		assert(method != nullptr);
	}
	
	void call(Args... args) override final
	{
		(m_object.*m_method)(args...);
	}

private:
	Object& m_object;
	Method  m_method;
};

template <class ...Args>
class FunctionHandler : public EventHandler<Args...>
{
using Function = void (*) (Widget*, Args...);

public:
	FunctionHandler(Function funciton):
		EventHandler<Args...>(),
		m_funciton(funciton)
	{
		assert(funciton != nullptr);
	}

	void call(Widget* wid, Args... args) override final
	{
		(*m_funciton)(wid, args...);
	}

private:
	Function m_funciton;
};

template <class ...Args>
class Signal
{
public:
	Signal()
	{

	}

	~Signal()
	{
		for (size_t i = 0; i < m_handlers.size(); i++)
			delete m_handlers[i];
		m_handlers.clear();
	}

	void operator()(Args... args)
	{
		for (size_t i = 0; i < m_handlers.size(); i++)
			m_handlers[i]->call(args...);
	}

	void operator+=(EventHandler<Args...>* eventHandler)
	{
		m_handlers.push_back(eventHandler);
	}

	Signal& operator=(const Signal& other) = delete;
	Signal(const Signal& other)            = delete;

private:
	std::vector<EventHandler<Args...>*> m_handlers = {};
};

template <class Object, class ...Args>
EventHandler<Args...>* newMethodHandler(Object& object, 
	                                    void (Object::*method) (Args...))
{
    return new MethodHandler<Object, Args...>(object, method);
}

template <class ...Args>
EventHandler<Args...>* newFunctionHandler(void (*funciton) (Args...))
{
    return new FunctionHandler<Args...>(funciton);
}

#define METHOD(Object, Method) newMethodHandler   (Object, &Method)
#define FUNCTION(Function)     newFunctionHandler (&Function)

#endif // SLOT_HPP
