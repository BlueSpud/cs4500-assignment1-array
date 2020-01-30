#include <stdio.h>
#include "array.h"
#include "object.h"  // Your file with the CwC declaration of Object
#include "string.h"  // Your file with the String class

void FAIL() { exit(1); }
void OK(const char *m) { printf("%s\n", m); }
void t_true(bool p) {
    if (!p) FAIL();
}
void t_false(bool p) {
    if (p) FAIL();
}

static const int _stressTestVal = 10000;

void arrayStressTest() {
    ArrayString *arr0 = new ArrayString();

    // Testing push_back
    for (int i = 0; i < _stressTestVal; i++) {
        char *charArr = new char(6);
        strcpy(charArr, "test");
        charArr[4] = i;
        charArr[5] = '\0';
        String *currStr = new String(charArr);
        arr0->push_back(currStr);

        delete charArr;
    }

    // Testing get
    t_true(arr0->size() == _stressTestVal);
    t_true(strcmp(arr0->get(38)->val_, "test38") == 0);

    // Testing set
    String *test38 = arr0->get(38);
    String *replace38 = new String("replace38");
    arr0->set(38, replace38);
    t_true(strcmp(arr0->get(38)->val_, "replace38") == 0);
    t_true(arr0->get(38)->hash() == replace38->hash());

    // Testing index_of
    t_true(arr0->index_of(test38) == arr0->size());
    t_true(arr0->index_of(replace38) == 38);

    delete test38;
    for (int i = 0; i < 10000; i++) {
        delete arr0->get(i);
    }
    delete arr0;
    OK("ArrayTest.arrayStressTestStr");
}

int main() { 
  arrayStressTest(); 
  return 0;
}