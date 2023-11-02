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
#define OMNITY_API_METHOD(CLASS, METHOD, ...) CLASS##__##METHOD(OMNITY_NAMESPACE::CObjectRef __ThisRef, ##__VA_ARGS__)
#define OMNITY_API_CTOR(CLASS, ...) OMNITY_NAMESPACE::CObjectRef CLASS##__Ctor(__VA_ARGS__)

#define OMNITY_API_CTOR_CREATE_OBJECT(CLASS, ...) (OMNITY_NAMESPACE::ObjectRef<OMNITY_NAMESPACE::CLASS>(new OMNITY_NAMESPACE::CLASS(__VA_ARGS__)).RequireManagedRef())

// Types
#include <cstdint>
#include <cfloat>
#include <type_traits>
#include <atomic>

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

class OmnityObject
{
public:
	virtual ~OmnityObject() = default;
};

struct ObjectRefState
{
	using Count = UInt;
	using AtomicCount = std::atomic<Count>;
	AtomicCount count = 0;
	OmnityObject* ptr = nullptr;
};

using CObjectRef = ObjectRefState*;

template<typename T>
class ObjectRef
{
private:
	CObjectRef _refInfo;
public:
	ObjectRef(T* ptr = nullptr)
	{
		_refInfo = new ObjectRefState();
		_refInfo->ptr = (OmnityObject*)ptr;
		++_refInfo->count;
	}
	ObjectRef(const ObjectRef& objRef)
	{
		_refInfo = objRef._refInfo;
		DangerousAddRef();
	}
	ObjectRef(ObjectRef&& objRef)
	{
		_refInfo = objRef._refInfo;
		objRef._refInfo = nullptr;
	}
	ObjectRef(CObjectRef cref)
	{
		_refInfo = cref;
		DangerousAddRef();
	}
	ObjectRef operator=(const ObjectRef& r)
	{
		if (r._refInfo == _refInfo) return *this;
		DangerousRelease();
		_refInfo = r._refInfo;
		DangerousAddRef();
		return *this;
	}
	T* operator->()
	{
		return (T*)_refInfo->ptr;
	}
	~ObjectRef()
	{
		DangerousRelease();
	}
	CObjectRef RequireManagedRef()
	{
		DangerousAddRef();
		return _refInfo;
	}
	static void DangerousAddRef(CObjectRef ref)
	{
		if (ref == nullptr) return;
		++(*ref).count;
	}
	static void DangerousRelease(CObjectRef ref)
	{
		if (ref == nullptr) return;
		if (--ref->count == 0)
			Dispose(ref);
	}
private:
	void DangerousAddRef()
	{
		DangerousAddRef(_refInfo);
	}
	void DangerousRelease()
	{
		DangerousRelease(_refInfo);
	}
	static void Dispose(CObjectRef ref)
	{
		delete ref->ptr;
		delete ref;
	}
};

OMNITY_END

// Version
#define OMNITY_MAKE_VERSION(MAJOR, MINOR, PATCH) (((OMNITY_NAMESPACE::ULong)MAJOR << 48) + ((OMNITY_NAMESPACE::ULong)MINOR << 32) + ((OMNITY_NAMESPACE::ULong)PATCH))
constexpr auto OMNITY_VERSION = OMNITY_MAKE_VERSION(1, 0, 0);