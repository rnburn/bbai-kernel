#include "median_salary2.h"

#include "bbai/base/test/unit_test.h"
#include "employee.h"
using namespace bbai;
using namespace bbai::medex;

TEST_CASE("we can compute median salary") {
  std::vector<employee> employees;

  SECTION("we can handle the single employee case") {
    employees.push_back(employee{10});
    REQUIRE(compute_median_salary2(employees.data(),
                                   employees.data() + employees.size()) == 10);
  }

  SECTION("we can handle two employees") {
    employees.push_back(employee{10});
    employees.push_back(employee{20});
    REQUIRE(compute_median_salary2(employees.data(),
                                   employees.data() + employees.size()) == 15);
  }

  SECTION("we can handle three employees") {
    employees.push_back(employee{10});
    employees.push_back(employee{20});
    employees.push_back(employee{5});
    REQUIRE(compute_median_salary2(employees.data(),
                                   employees.data() + employees.size()) == 10);
  }
}
