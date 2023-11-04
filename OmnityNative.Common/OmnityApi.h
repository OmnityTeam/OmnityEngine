#pragma once

constexpr auto OMNITY_PLATFORM_ID_WINDOWS = 1;
constexpr auto OMNITY_PLATFORM_ID_ANDROID = 2;
constexpr auto OMNITY_PLATFORM_ID_IOS = 3;

#define OMNITY_NAMESPACE OmnityNative

#define OMNITY_BEGIN namespace OMNITY_NAMESPACE {\
// Retain an empty line here! Do not delete the current commited line!
#define OMNITY_END }

#if defined _WIN32
#define OMNITY_PLATFORM_WINDOWS
constexpr auto OMNITY_PLATFORM_ID = OMNITY_PLATFORM_ID_WINDOWS;
#elif defined __ANDROID__
#define OMNITY_PLATFORM_ANDROID
constexpr auto OMNITY_PLATFORM_ID = OMNITY_PLATFORM_ID_ANDROID;
#endif

#if defined OMNITY_PLATFORM_WINDOWS
#define OMNITY_API_EXPORT extern "C" __declspec(dllexport)
#elif defined OMNITY_PLATFORM_ANDROID
#define OMNITY_API_EXPORT extern "C"
#endif

#define OMNITY_DEFINE_THIS(CLASS) OMNITY_NAMESPACE::ObjectRef<OMNITY_NAMESPACE::CLASS> This(__ThisRef)

#define OMNITY_API_STATIC_METHOD(CLASS, METHOD, ...) CLASS##__##METHOD(__VA_ARGS__)
#define OMNITY_API_METHOD(CLASS, METHOD, ...) CLASS##__##METHOD(OMNITY_NAMESPACE::CObjectRef* __ThisRef, ##__VA_ARGS__)
#define OMNITY_API_CTOR(CLASS, ...) OMNITY_NAMESPACE::CObjectRef* CLASS##__Ctor(__VA_ARGS__)

#define OMNITY_API_CTOR_CREATE_OBJECT(CLASS, ...) (OMNITY_NAMESPACE::ObjectRef<OMNITY_NAMESPACE::CLASS>::New(__VA_ARGS__).RequireManagedRef())

#include <atomic>

// Types
#include <cstdint>
#include <cfloat>
#include <type_traits>

OMNITY_BEGIN
using Short = int16_t;
using UShort = uint16_t;
using Int = int32_t;
using UInt = uint32_t;
using Long = int64_t;
using ULong = uint64_t;
using String = const char*;
using Bool = bool;
using Float = float;
using Double = double;

// Object counter
#define OMNITY_ENABLE_OBJECT_COUNTER

#ifdef OMNITY_ENABLE_OBJECT_COUNTER
extern std::atomic<ULong> OmnityObjectCount;
extern std::atomic<ULong> OmnitySharedObjectCount;
#endif

struct ObjectRefState
{
	using Destructor = void(*)(ObjectRefState*);
	using Count = UInt;
	using AtomicCount = std::atomic<Count>;
	AtomicCount count = 0;
	void* ptr = nullptr;
	Destructor destructor;
};

struct CObjectRef
{
	using CRelease = void(*)(CObjectRef*);
	ObjectRefState* refInfo;
	void* ptr;
	CRelease release;
};

template<typename T>
class EnableRefFromThis;

template<typename T>
class ObjectRef
{
private:
	ObjectRefState* _refInfo;
	T* _ptr;

	template<class T2,
		typename std::enable_if <
		std::is_base_of<EnableRefFromThis<T2>, T2>{},
		bool> ::type = true >
	inline void BindThisRef(T2 * ptr)
	{
		dynamic_cast<EnableRefFromThis<T2>*>(ptr)->_thisRef = _refInfo;
		dynamic_cast<EnableRefFromThis<T2>*>(ptr)->_ptr = _ptr;
	}

	template<class T2,
		typename std::enable_if <
		!std::is_base_of<EnableRefFromThis<T2>, T2>{},
		bool > ::type = true>
	inline void BindThisRef(T2 * ptr) {}

	ObjectRef(T* ptr)
	{
#ifdef OMNITY_ENABLE_OBJECT_COUNTER
		++OmnityObjectCount;
#endif
		_refInfo = new ObjectRefState();
		_refInfo->ptr = ptr;
		_refInfo->destructor = &ObjectRef<T>::Destructor;
		_ptr = ptr;
		++_refInfo->count;
		BindThisRef(_ptr);
	}
public:
	ObjectRef(std::nullptr_t ptr = nullptr)
	{
		_refInfo = nullptr;
		_ptr = nullptr;
	}
	template<typename... TArgs>
	static ObjectRef<T> New(TArgs... args)
	{
		return ObjectRef<T>(new T(args...));
	}

	ObjectRef(const ObjectRef& objRef)
	{
		_refInfo = objRef._refInfo;
		_ptr = objRef._ptr;
		DangerousAddRef();
	}
	ObjectRef(ObjectRef&& objRef) noexcept
	{
		_refInfo = objRef._refInfo;
		_ptr = objRef._ptr;
		objRef._refInfo = nullptr;
	}
	ObjectRef(CObjectRef* cref) : ObjectRef(cref->refInfo, reinterpret_cast<T*>(cref->ptr)) {}
	ObjectRef(ObjectRefState* cref, T* ptr)
	{
		_refInfo = cref;
		_ptr = ptr;
		DangerousAddRef();
		BindThisRef(_ptr);
	}
	template<typename TTo>
	ObjectRef<TTo> CastTo() const
	{
		return ObjectRef<TTo>(_refInfo, dynamic_cast<TTo*>(reinterpret_cast<T*>(_ptr)));
	}
	ObjectRef operator=(const ObjectRef& r)
	{
		if (r._refInfo == _refInfo) return *this;
		DangerousRelease();
		_refInfo = r._refInfo;
		DangerousAddRef();
		_ptr = r._ptr;
		return *this;
	}
	T* operator->() const
	{
		return _ptr;
	}
	~ObjectRef()
	{
		DangerousRelease();
	}
	CObjectRef* RequireManagedRef() const
	{
		DangerousAddRef();
		auto cRef = new CObjectRef();
		cRef->refInfo = _refInfo;
		cRef->ptr = _ptr;
		cRef->release = &ObjectRef<T>::DangerousCRelease;
#ifdef OMNITY_ENABLE_OBJECT_COUNTER
		++OmnitySharedObjectCount;
#endif
		return cRef;
	}
private:
	inline void DangerousAddRef() const
	{
		DangerousAddRef(_refInfo, _ptr);
	}
	inline void DangerousRelease() const
	{
		DangerousRelease(_refInfo, _ptr);
	}
	static inline void DangerousAddRef(ObjectRefState* ref, T* ptr)
	{
		if (ref == nullptr) return;
		++(*ref).count;
	}
	static inline void DangerousRelease(ObjectRefState* ref, T* ptr)
	{
		if (ref == nullptr) return;
		if (--ref->count == 0)
			ref->destructor(ref);
	}
	static inline void DangerousAddCRef(CObjectRef* ref)
	{
		DangerousAddRef(ref->refInfo, reinterpret_cast<T*>(ref->ptr));
	}
	static inline void DangerousCRelease(CObjectRef* ref)
	{
		DangerousRelease(ref->refInfo, reinterpret_cast<T*>(ref->ptr));
	}
	static void Destructor(ObjectRefState* ref)
	{
		delete reinterpret_cast<T*>(ref->ptr); ref->ptr = 0;
		delete ref;
#ifdef OMNITY_ENABLE_OBJECT_COUNTER
		--OmnityObjectCount;
#endif
	}
};

template<typename T>
class EnableRefFromThis
{
	friend class ObjectRef<T>;
private:
	ObjectRefState* _thisRef;
	T* _ptr;

public:
	ObjectRef<T> GetObjectRef()
	{
		return ObjectRef<T>(_thisRef, _ptr);
	}
};

OMNITY_END

// Version
#define OMNITY_MAKE_VERSION(MAJOR, MINOR, PATCH) (((OMNITY_NAMESPACE::ULong)MAJOR << 48) + ((OMNITY_NAMESPACE::ULong)MINOR << 32) + ((OMNITY_NAMESPACE::ULong)PATCH))
constexpr auto OMNITY_VERSION = OMNITY_MAKE_VERSION(1, 0, 0);