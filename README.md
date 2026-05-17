# nlohmann_json_reflection

Universal reflection-based serialization and deserialization for
[nlohmann/json](https://github.com/nlohmann/json#serialization--deserialization)

`nlohmann_json_reflection` provides a lightweight way to automatically serialize and deserialize structs, enums, and bitmask enums using custom `adl_serializer` specializations.

---

# Features

* Automatic JSON serialization/deserialization
* Works with plain structs/classes
* Enum support
* Bitmask enum support
* Minimal boilerplate

---

# Basic Usage

## Struct Serialization

```cpp
struct JSON_STRUCT
{
    std::string JSON;
    int STRUCT;
};

template <>
struct nlohmann::adl_serializer<JSON_STRUCT>
    : universal_serializer {};
```

### Example

```cpp
JSON_STRUCT data;
data.JSON = "hello";
data.STRUCT = 42;

nlohmann::json j = data;

// Result:
// {
//   "JSON": "hello",
//   "STRUCT": 42
// }
```

---

# Enum Serialization

## Standard Enum

```cpp
enum TST_ENUM
{
    TST,
    ENUM
};

template <>
struct nlohmann::adl_serializer<TST_ENUM>
    : universal_serializer {};
```

### Example

```cpp
TST_ENUM value = ENUM;

nlohmann::json j = value;

// Result:
// {
//   "ENUM"
// }
```

---

# Bitmask Enum Serialization

For bitmask enums, use `universal_serializer_msk`.

```cpp
enum TST_ENUM_MSK
{
    FLAG_A = 1 << 0,
    FLAG_B = 1 << 1
};

void operator|=(TST_ENUM_MSK& lhs, const TST_ENUM_MSK& rhs)
{
    lhs = static_cast<TST_ENUM_MSK>(
        static_cast<size_t>(lhs) |
        static_cast<size_t>(rhs)
    );
}

template <>
struct nlohmann::adl_serializer<TST_ENUM_MSK>
    : universal_serializer_msk {};
```

### Example

```cpp
TST_ENUM_MSK flags = FLAG_A;
flags |= FLAG_B;

nlohmann::json j = flags;

// Result:
// {
//   "FLAG_A",
//   "FLAG_B"
// }
```

---

# Requirements

* C++26 or newer
* [nlohmann/json](https://github.com/nlohmann/json)

---

# Motivation

Writing manual `to_json` / `from_json` functions for every type quickly becomes repetitive.
This library reduces the required boilerplate to a single serializer specialization.

---

# License

MIT License

---