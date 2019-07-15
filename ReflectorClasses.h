#pragma once

#include <typeindex>
#include <vector>

namespace Reflector
{
	struct ClassReflectionData;
	struct FieldReflectionData;
	struct MethodReflectionData;

	struct ClassReflectionData
	{
		const char* Name = "";
		const char* ParentClassName = "";
		const char* Properties = "{}";
#ifdef NLOHMANN_JSON_VERSION_MAJOR
		nlohmann::json PropertiesJSON;
#endif
		void* (*Constructor)(const ::Reflector::ClassReflectionData&) = {};

		/// These are vectors and not e.g. initializer_list's because you might want to create your own classes
		std::vector<FieldReflectionData> Fields; 
		std::vector<MethodReflectionData> Methods;

		std::type_index TypeIndex;
	};

	struct FieldReflectionData
	{
		const char* Name = "";
		const char* FieldType = "";
		const char* Initializer = "";
		const char* Properties = "{}";
#ifdef NLOHMANN_JSON_VERSION_MAJOR
		nlohmann::json PropertiesJSON;
#endif
		std::type_index FieldTypeIndex;

		ClassReflectionData const* ParentClass = nullptr;
	};

	struct MethodReflectionData
	{
		const char* Name = "";
		const char* ReturnType = "";
		const char* Parameters = "";
		const char* Properties = "{}";
#ifdef NLOHMANN_JSON_VERSION_MAJOR
		nlohmann::json PropertiesJSON;
#endif
		std::type_index ReturnTypeIndex;

		ClassReflectionData const* ParentClass = nullptr;
	};

	struct EnumeratorReflectionData
	{
		const char* Name = "";
		int64_t Value;
	};

	struct EnumReflectionData
	{
		const char* Name = "";
		const char* Properties = "{}";
		std::vector<EnumeratorReflectionData> Enumerators;
		std::type_index TypeIndex;
	};

	struct Reflectable
	{
		virtual ClassReflectionData const& GetReflectionData() const
		{
			static const ClassReflectionData data = { 
				.Name = "Reflectable",
				.ParentClassName = "",
				.Properties = "",
#ifdef NLOHMANN_JSON_VERSION_MAJOR
				.PropertiesJSON = ::nlohmann::json::object(),
#endif
				.TypeIndex = typeid(Reflectable)
			}; 
			return data;
		}

		Reflectable() noexcept = default;
		Reflectable(::Reflector::ClassReflectionData const& klass) noexcept : mClass(&klass) {}

		virtual ~Reflectable() = default;

	protected:

		ClassReflectionData const* mClass = nullptr;
	};
}