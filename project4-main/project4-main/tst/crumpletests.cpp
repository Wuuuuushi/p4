#include <CrumpleTree.hpp>
#include <catch2/catch_amalgamated.hpp>

namespace {
namespace proj4 = shindler::ics46::project4;

/* Remember, these are prerequisites to having us grade
    the related part of the assignment.  These are not
    worth points on their own, nor are they comprehensive.

    REMEMBER TO TEST YOUR OWN CODE COMPREHENSIVELY.

*/

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
// readability-magic-numbers)

TEST_CASE("Insert:Case2Left",
          "[Insert][Cases]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "");
    tree.insert(18, "");

    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(18));

    REQUIRE(tree.level(20) == 2);
    REQUIRE(tree.level(18) == 1);

    std::vector<int> inExp = {18, 20};
    REQUIRE(tree.inOrder() == inExp);
}

TEST_CASE("Insert:Case3Left",
          "[Insert][Cases]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "");
    tree.insert(19, "");
    tree.insert(18, "");

    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(18));

    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(18) == 1);

    std::vector<int> inExp = {18, 19, 20};
    REQUIRE(tree.inOrder() == inExp);
}

TEST_CASE("Insert:Case5Left",
          "[Insert][Cases]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "");
    tree.insert(18, "");
    tree.insert(19, "");

    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(19));

    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 1);
    REQUIRE(tree.level(19) == 2);

    std::vector<int> inExp = {18, 19, 20};
    REQUIRE(tree.inOrder() == inExp);
}

TEST_CASE("Insert:Case2Right",
          "[Insert][Cases]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(20, "");

    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(18));

    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 2);

    std::vector<int> inExp = {18, 20};
    REQUIRE(tree.inOrder() == inExp);
}

TEST_CASE("Insert:Case3Right",
          "[Insert][Cases]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");

    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(18));

    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(18) == 1);
}

TEST_CASE("Insert:Case5Right",
          "[Insert][Cases]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(20, "");
    tree.insert(19, "");

    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(19));

    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 1);
    REQUIRE(tree.level(19) == 2);
}
TEST_CASE("Tree:SimpleInsertAndFind:ExpectSingleInsertFound",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");

    REQUIRE(tree.contains(5));
}

TEST_CASE("Tree:DoubleInsert:ExpectFindSecondInsert",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(10, "bar");

    REQUIRE(tree.contains(10));
}

TEST_CASE("Tree:QuadInsert:ExpectFindFindTwoHopsAway",
          "[Required][Basic][Insert][Contains]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");

    REQUIRE(tree.contains(12));
}

TEST_CASE("Tree:5Inserts:ExpectSize5", "[Required][Basic][Insert][Size]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    REQUIRE(tree.size() == 5);
}

TEST_CASE("Tree:5Inserts:ExpectSize5INORDER", "[Required][Basic][Insert][Size]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    REQUIRE(tree.size() == 5);
    auto trav = tree.inOrder();
    static const std::vector<int> expected = {3,5,10,12,15};
    REQUIRE(trav == expected);
}

TEST_CASE("Tree:5Inserts:ExpectSize5PREORDER", "[Required][Basic][Insert][Size]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");

    REQUIRE(tree.level(5) == 1);
    tree.insert(3, "sna");
    REQUIRE(tree.level(5) == 2);
    REQUIRE(tree.level(3) == 1);
    tree.insert(10, "bar");
    REQUIRE(tree.level(5) == 2);
    REQUIRE(tree.level(3) == 1);
    REQUIRE(tree.level(10) == 1);
    tree.insert(12, "twelve");
    REQUIRE(tree.level(5) == 3);
    REQUIRE(tree.level(3) == 1);
    REQUIRE(tree.level(10) == 2);
    REQUIRE(tree.level(12) == 1);
    tree.insert(15, "fifteen");

    REQUIRE(tree.size() == 5);
    auto trav = tree.preOrder();
    static const std::vector<int> expected = {5,3,12,10,15};
    REQUIRE(trav == expected);
}

TEST_CASE("Tree:DoAPostOrder:ExpectCorrectPostorderTraversal",
          "[Required][Basic][Insert][PostOrder]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    auto trav = tree.postOrder();
    static const std::vector<int> expected = {3, 10, 5};
    REQUIRE(trav == expected);
}

TEST_CASE("Tree:InsertsPaper1", "[Required][Basic][Insert][Size]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "foo");
    tree.insert(19, "sna");
    tree.insert(18, "bar");
    REQUIRE(tree.size() == 3);

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 1);

    auto trav1 = tree.inOrder();
    static const std::vector<int> expected = {18,19,20};
    REQUIRE(trav1 == expected);

    std::cout << "Finishes first one" << std::endl;
    tree.insert(12, "BOO");

    REQUIRE(tree.size() == 4);


    REQUIRE(tree.level(19) == 3);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 2);
    REQUIRE(tree.level(12) == 1);

    auto trav2 = tree.inOrder();
    static const std::vector<int> expected2 = {12,18,19,20};
    REQUIRE(trav2 == expected2);

    std::cout << "Finishes second" << std::endl;
    tree.insert(9, "SOO");

    REQUIRE(tree.size() == 5);

    REQUIRE(tree.level(19) == 3);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 1);
    REQUIRE(tree.level(12) == 2);
    REQUIRE(tree.level(9) == 1);

    auto trav3 = tree.inOrder();
    static const std::vector<int> expected3 = {9,12,18,19,20};
    REQUIRE(trav3 == expected3);

    std::cout << "Finishes third" << std::endl;
    tree.insert(17, "SA");

    REQUIRE(tree.size() == 6);

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 3);
    REQUIRE(tree.level(12) == 2);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(17) == 1);
    
    
    
    auto trav4 = tree.inOrder();
    static const std::vector<int> expected4 = {9,12,17,18,19,20};
    REQUIRE(trav4 == expected4);

    std::cout << "Finishes fourth" << std::endl;
    tree.insert(7, "AS");
    REQUIRE(tree.size() == 7);

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 3);
    REQUIRE(tree.level(9) == 2);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(7) == 1);

    auto trav5 = tree.inOrder();
    static const std::vector<int> expected5 = {7,9,12,17,18,19,20};
    REQUIRE(trav5 == expected5);
    std::cout << "Finishes sixth" << std::endl;
    tree.insert(5, "ASDSA");
    REQUIRE(tree.size() == 8);

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 3);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(7) == 2);
    REQUIRE(tree.level(5) == 1);

    auto trav6 = tree.inOrder();
    static const std::vector<int> expected6 = {5,7,9,12,17,18,19,20};
    REQUIRE(trav6 == expected6);

    std::cout << "Finishes seventh" << std::endl;
    tree.insert(13, "ASDSA23");
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 3);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(7) == 2);
    REQUIRE(tree.level(13) == 1);
    REQUIRE(tree.level(5) == 1);
    tree.insert(15, "ASDSADC");

    REQUIRE(tree.size() == 10);

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 3);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(7) == 2);
    REQUIRE(tree.level(15) == 2);
    REQUIRE(tree.level(13) == 1);

    auto trav7 = tree.inOrder();
    static const std::vector<int> expected7 = {5,7,9,12,13,15,17,18,19,20};
    REQUIRE(trav7 == expected7);
    std::cout << "Finishes eigth" << std::endl;
    tree.insert(6, "AS211DSADC");

    REQUIRE(tree.size() == 11);

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 3);
    REQUIRE(tree.level(12) == 4);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(7) == 3);
    REQUIRE(tree.level(15) == 2);
    REQUIRE(tree.level(13) == 1);
    REQUIRE(tree.level(6) == 1);
    REQUIRE(tree.level(5) == 2);
    auto trav8 = tree.inOrder();
    static const std::vector<int> expected8 = {5,6,7,9,12,13,15,17,18,19,20};
    REQUIRE(trav8 == expected8);
    std::cout << "Finishes ninth" << std::endl;
    tree.insert(16, "AS211D123SADC");

    REQUIRE(tree.size() == 12);

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 5);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(7) == 3);
    REQUIRE(tree.level(15) == 3);
    REQUIRE(tree.level(13) == 1);
    REQUIRE(tree.level(6) == 1);
    REQUIRE(tree.level(5) == 2);
    REQUIRE(tree.level(16) == 1);
    auto trav9 = tree.inOrder();
    static const std::vector<int> expected9 = {5,6,7,9,12,13,15,16,17,18,19,20};
    REQUIRE(trav9 == expected9);
    std::cout << "Finishes tenth" << std::endl;
    tree.insert(14, "AS211232D123SADC");

    REQUIRE(tree.size() == 13);
    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(18) == 4);
    REQUIRE(tree.level(12) == 5);
    REQUIRE(tree.level(9) == 1);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(7) == 3);
    REQUIRE(tree.level(15) == 3);
    REQUIRE(tree.level(13) == 2);
    REQUIRE(tree.level(6) == 1);
    REQUIRE(tree.level(5) == 2);
    REQUIRE(tree.level(16) == 1);
    REQUIRE(tree.level(14) == 1);
    auto trav10 = tree.inOrder();
    static const std::vector<int> expected10 = {5,6,7,9,12,13,14,15,16,17,18,19,20};
    REQUIRE(trav10 == expected10);



}

TEST_CASE("Tree:RemoveDoesARemove:ExpectElementsNotInTreeAndLevelsCorrect",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(12));
    REQUIRE(tree.contains(9));
    tree.remove(9);
    tree.remove(18);
    // What happens?  12 is now a leaf and must fall.  But 19 is a (2,2) and
    // remains at level 3.
    REQUIRE(!tree.contains(9));
    REQUIRE(!tree.contains(18));
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(12) == 1);
    REQUIRE(tree.level(19) == 3);
}

TEST_CASE("Tree:RemoveDoesARemove:ExpectElementsNotInTreeAndLevelsCorrectPAPER",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(44, "AASD");
    tree.insert(17, "ASD");
    tree.insert(78, "ASDWSS");
    tree.insert(32, "ASDWWWW");
    tree.insert(50, "CZMX");
    tree.insert(87, "ASDAWSX");
    tree.insert(48,"ASDASDXZ");
    tree.insert(62, "ASDASDADWAS");

    REQUIRE(tree.level(44) == 4);
    REQUIRE(tree.level(78) == 3);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(50) == 2);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(tree.level(48) == 1);
    REQUIRE(tree.level(62) == 1);
    REQUIRE(tree.level(87) == 1);

    tree.remove(48);

    REQUIRE(tree.level(44) == 4);
    REQUIRE(tree.level(78) == 3);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(50) == 2);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(!tree.contains(48));
    REQUIRE(tree.level(62) == 1);
    REQUIRE(tree.level(87) == 1);

    tree.remove(62);

    REQUIRE(tree.level(44) == 4);
    REQUIRE(tree.level(78) == 3);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(50) == 1);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(!tree.contains(48));
    REQUIRE(!tree.contains(62));
    REQUIRE(tree.level(87) == 1);

    tree.insert(48, "ASDWASSXXZ");
    REQUIRE(tree.level(44) == 4);
    REQUIRE(tree.level(78) == 3);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(50) == 2);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(tree.level(48) == 1);
    REQUIRE(!tree.contains(62));
    REQUIRE(tree.level(87) == 1);

    tree.insert(62, "ASDWASXCZ");
    REQUIRE(tree.level(44) == 4);
    REQUIRE(tree.level(78) == 3);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(50) == 2);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(tree.level(48) == 1);
    REQUIRE(tree.level(62) == 1);
    REQUIRE(tree.level(87) == 1);

    tree.remove(62);
    tree.remove(87);

    REQUIRE(tree.level(44) == 4);
    REQUIRE(tree.level(78) == 1);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(50) == 2);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(tree.level(48) == 1);
    REQUIRE(!tree.contains(62));
    REQUIRE(!tree.contains(87));

}

TEST_CASE("Tree:RemoveDoesARemove:ExpectElementsNotInTreeAndLevelsCorrectPAPER2",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(44, "ASDS");
    tree.insert(17,"!@#!@#");
    tree.insert(78, "ASDWA");
    tree.insert(32, "ASDASDASDSAD");
    tree.insert(50, "ASDWA");
    tree.insert(87, "ASDW)");

    tree.remove(87);
    tree.remove(50);

    REQUIRE(tree.level(44) == 3);
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(tree.level(78) == 1);
    REQUIRE(!tree.contains(87));
    REQUIRE(!tree.contains(50));
    REQUIRE(tree.size() == 4);

}

TEST_CASE("Tree:RemoveDoesARemove:ExpectElementsNotInTreeAndLevelsCorrectROOT",
          "[Required][Insert][Erase][Contains][Level]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(44, "ASDS");
    tree.insert(17,"!@#!@#");
    tree.insert(78, "ASDWA");
    tree.insert(32, "ASDASDASDSAD");
    tree.insert(50, "ASDWA");
    tree.insert(87, "ASDW)");

    tree.remove(44);
    tree.remove(87);

    REQUIRE(!tree.contains(44));
    REQUIRE(tree.level(17) == 2);
    REQUIRE(tree.level(32) == 1);
    REQUIRE(tree.level(78) == 1);
    REQUIRE(!tree.contains(87));
    REQUIRE(tree.level(50) == 3);

    auto trav10 = tree.inOrder();
    static const std::vector<int> expected10 = {17,32,50,78};
    REQUIRE(trav10 == expected10);

    auto trav9 = tree.preOrder();
    static const std::vector<int> expected9 = {50,17,32,78};
    REQUIRE(trav9 == expected9);

    auto trav8 = tree.postOrder();
    static const std::vector<int> expected8 = {32,17,78,50};
    REQUIRE(trav8 == expected8);

}

TEST_CASE("Delete:Case1ALeft", "[Delete][Cases][Left][1A]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");

    tree.remove(18);
    

    REQUIRE(!tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(20)); 

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
}

TEST_CASE("Delete:Case1ARight", "[Delete][Cases][Right][1A]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");

    tree.remove(20);

    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(!tree.contains(20)); 

    REQUIRE(tree.level(18) == 1);
    REQUIRE(tree.level(19) == 2);
}

TEST_CASE("Delete:Case1BLeft", "[Delete][Cases][Left][1B]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");

    tree.remove(20);
    tree.remove(18);
    

    REQUIRE(!tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(!tree.contains(20)); 

    REQUIRE(tree.level(19) == 1);
}

TEST_CASE("Delete:Case1BRight", "[Delete][Cases][Right][1B]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");

    tree.remove(18);
    tree.remove(20);

    REQUIRE(!tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(!tree.contains(20)); 

    REQUIRE(tree.level(19) == 1);
}

TEST_CASE("Delete:Case2Left", "[Delete][Cases][Left][2]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");
    tree.insert(17, "");

    tree.remove(17);
    tree.remove(18);
    
    REQUIRE(!tree.contains(17));
    REQUIRE(!tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(20)); 

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(20) == 1);
}

TEST_CASE("Delete:Case2Right", "[Delete][Cases][Right][2]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");
    tree.insert(21, "");

    tree.remove(21);
    tree.remove(20);
    
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(!tree.contains(20));
    REQUIRE(!tree.contains(21));

    REQUIRE(tree.level(18) == 1);
    REQUIRE(tree.level(19) == 2);
}

TEST_CASE("Delete:Case3Left", "[Delete][Cases][Left][3]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(21, "");
    tree.insert(22, "");
    tree.insert(20, "");

    tree.remove(18);
    
    REQUIRE(!tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(21));
    REQUIRE(tree.contains(22)); 

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(21) == 3);
    REQUIRE(tree.level(20) == 1);
    REQUIRE(tree.level(22) == 1);
}

TEST_CASE("Delete:Case3Right", "[Delete][Cases][Right][3]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(17, "");
    tree.insert(19, "");
    tree.insert(20, "");
    tree.insert(16, "");
    tree.insert(18, "");

    tree.remove(20);
    
    REQUIRE(tree.contains(17));
    REQUIRE(tree.contains(19));
    REQUIRE(!tree.contains(20));
    REQUIRE(tree.contains(16));
    REQUIRE(tree.contains(18)); 

    REQUIRE(tree.level(19) == 2);
    REQUIRE(tree.level(17) == 3);
    REQUIRE(tree.level(16) == 1);
    REQUIRE(tree.level(18) == 1);
}

TEST_CASE("Delete:Case4BLeft", "[Delete][Cases][Left][4B]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");
    tree.insert(21, "");

    tree.remove(18);
    
    REQUIRE(!tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(tree.contains(20));
    REQUIRE(tree.contains(21)); 

    REQUIRE(tree.level(19) == 1);
    REQUIRE(tree.level(20) == 2);
    REQUIRE(tree.level(21) == 1);
}

TEST_CASE("Delete:Case4BRight", "[Delete][Cases][Right][4B]") {
    proj4::CrumpleTree<int, std::string> tree;
    tree.insert(18, "");
    tree.insert(19, "");
    tree.insert(20, "");
    tree.insert(17, "");
    

    tree.remove(20);
    
    REQUIRE(tree.contains(17));
    REQUIRE(tree.contains(18));
    REQUIRE(tree.contains(19));
    REQUIRE(!tree.contains(20));
     
    REQUIRE(tree.level(17) == 1);
    REQUIRE(tree.level(18) == 2);
    REQUIRE(tree.level(19) == 1);
    
}



// NOLINTEND

}  // namespace
