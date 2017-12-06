#include "UnitTestFramework.h"
#include "slist.cpp"
#include <sstream>

SList* createTestList() {
  SList* l = new SList;
  SList* l1 = new SList;
  l1->insertEnd(new SInt(1));
  SList* l2 = new SList;
  l2->insertEnd(new SInt(2));
  l1->insertEnd(l2);
  SList* l3 = new SList;
  SList* l4 = new SList;
  SList* l5 = new SList;
  l5->insertEnd(new SInt(3));
  l4->insertEnd(l5);
  l4->insertEnd(new SInt(4));
  l3->insertEnd(l4);
  SList* l6 = new SList;
  l6->insertEnd(new SInt(5));
  SList* l7 = new SList;
  l7->insertEnd(new SInt(6));
  l6->insertEnd(l7);
  l3->insertEnd(l6);
  l3->insertEnd(new SList);
  SList* l8 = new SList;
  l8->insertEnd(new SInt(7));
  l3->insertEnd(l8);
  l->insertEnd(l3);
  l->insertEnd(new SInt(8));
  return l;
}

SList* createTestList2() {
  return
    (new SList)
    ->add((new SList)
          ->add(new SInt(1))
          ->add((new SList)
                ->add(new SInt(2))))
    ->add((new SList)
          ->add((new SList)
                ->add((new SList)
                      ->add(new SInt(3)))
                ->add(new SInt(4)))
                      
          ->add((new SList)
                ->add(new SInt(5))
                ->add((new SList)
                      ->add(new SInt(6))))
          ->add(new SList)
          ->add((new SList)
                ->add(new SInt(7))))
    ->add(new SInt(8));
}

TEST_CASE("SList", SList_PrintTest) {
  std::ostringstream oss;
  SList* l = createTestList2();
  oss << (*l);
  Assert::AreEqual(oss.str(), std::string("((1 (2)) (((3) 4) (5 (6)) () (7)) 8)"));
  delete l;
}

TEST_CASE("SList", SList_CollectTest) {
  LinkedList<int> result;
  SList* l = createTestList2();
  l->collect(result);
  int i = 1;
  for(LinkedList<int>::I it = result.begin(); it; ++it, ++i)
    Assert::AreEqual(i, *it);
  Assert::IsTrue(i == 9);
  delete l;
}
