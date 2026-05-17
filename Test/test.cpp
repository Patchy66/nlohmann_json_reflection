#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <nlohmann/json.hpp>
#pragma GCC diagnostic pop

#include <string.h>

#include <meta>
#include <fstream>
#include "json_refl.hpp"
#include <catch2/catch_test_macros.hpp>

using json = nlohmann::json;

struct JSON_STRUCT
{
  std::string JSON;
  int STRUCT;
};
template <> struct nlohmann::adl_serializer<JSON_STRUCT> : universal_serializer {};

TEST_CASE("test struct")
{
  JSON_STRUCT json_struct{.JSON = "JSON", .STRUCT = 1234};
  json js;

  js = json_struct;

  REQUIRE(js["JSON"] == json_struct.JSON);
  REQUIRE(js["STRUCT"] == json_struct.STRUCT);

  std::ofstream o("./result_struct.json");
  if (o.is_open())
  {
    o << std::setw(4) << js << std::endl;
    o.close();
    return;
  }
}

enum TST_ENUM
{
  TST,
  ENUM
};
template <> struct nlohmann::adl_serializer<TST_ENUM> : universal_serializer {};

TEST_CASE("enum")
{

  json js;
  TST_ENUM tst_enum;

  tst_enum = TST;
  js["TST"] = tst_enum;
  tst_enum = ENUM;
  js["ENUM"] = tst_enum;

  REQUIRE(js["TST"] == TST);
  REQUIRE(js["ENUM"] == ENUM);

  std::string string_tst_1 = js["TST"];
  std::string string_tst_2 = js["ENUM"];

  REQUIRE(string_tst_1 == "TST");
  REQUIRE(string_tst_2 == "ENUM");

  std::ofstream o("./result_enum.json");
  if (o.is_open())
  {
    o << std::setw(4) << js << std::endl;
    o.close();
    return;
  }
}

enum TST_ENUM_MSK
{
  TST_MSK,
  ENUM_MSK
};
template <> struct nlohmann::adl_serializer<TST_ENUM_MSK> : universal_serializer_msk {};

void operator|=(TST_ENUM_MSK &lhs, const TST_ENUM_MSK &rhs)
{
  lhs = static_cast<TST_ENUM_MSK>(static_cast<size_t>(lhs) | static_cast<size_t>(rhs));
}

TEST_CASE("enum msk")
{
  json js;
  TST_ENUM_MSK tst_enum_msk;

  tst_enum_msk  = (TST_ENUM_MSK)(1 << TST_MSK);  
  tst_enum_msk |= (TST_ENUM_MSK)(1 << ENUM_MSK); 

  js = tst_enum_msk; 

  REQUIRE(js == TST_ENUM_MSK(1 << TST_MSK | 1 << ENUM_MSK));

  std::string tst_string_1 = js[0];
  std::string tst_string_2 = js[1];

  REQUIRE(tst_string_1 == "TST_MSK");
  REQUIRE(tst_string_2 == "ENUM_MSK");


  std::ofstream o("./result_enum_msk.json");
  if (o.is_open())
  {
    o << std::setw(4) << js << std::endl;
    o.close();
    return;
  }
}