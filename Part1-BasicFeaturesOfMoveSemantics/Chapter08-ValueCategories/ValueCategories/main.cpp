#include "history_of_value_category.h"
#include "value_categoriescpp11.h"
#include "value_categoriescpp17.h"
#include "special_rules_for_value_categories.h"

int main()
{
    history_value_categories();
    value_categories();
    value_categories_cpp17();

    value_category_of_func();
    test_data_member_value_categories();
    return 0;
}
