package seedu.duke;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class CommandsTest {
    @Test
    public void addGoodTest() {
        //test 1, adding good normally - success
        ArrayList<Good> goodsArrayList = new ArrayList<>();
        Commands.addGood("1", "chairs", "15", goodsArrayList);
        assertEquals(1, goodsArrayList.size());

        /*
        //test 2, adding non-unique id with different name - fail, good is not added
        Commands.addGood("1", "tables", "15", goodsArrayList);
        assertEquals(1, goodsArrayList.size());
        */

        goodsArrayList = new ArrayList<>();
        //test 3, blank inputs - fail, good is not added
        Commands.addGood("1", "     ", "15", goodsArrayList);
        assertEquals(0, goodsArrayList.size());

        //test 4, empty inputs - fail, good is not added
        Commands.addGood("1", "", "15", goodsArrayList);
        assertEquals(0, goodsArrayList.size());

        //test 5, non-numerical inputs for id - fail, good is not added
        Commands.addGood("hi", "chairs", "15", goodsArrayList);
        assertEquals(0, goodsArrayList.size());
    }

    @Test
    void removeGoodTest() {
        ArrayList<Good> goodsArrayList = new ArrayList<>();
        Commands.addGood("1", "chairs", "15", goodsArrayList);
        Commands.addGood("2", "table", "15", goodsArrayList);

        /*
        //test 1, delete all (15) chairs - success, only left tables in list
        Commands.removeGood("1", "15", goodsArrayList);
        assertEquals(1, goodsArrayList.size());
        */

        //test 2, delete 1 table - success, 14 tables left
        Commands.removeGood("2", "1", goodsArrayList);
        assertEquals(14, goodsArrayList.get(1).getQuantity());

        //test 3, delete 16 tables - fail, deleting more than expected
        Commands.removeGood("2", "16", goodsArrayList);
        assertEquals(14, goodsArrayList.get(1).getQuantity());

        //test 4, non-numerical inputs - fail, good is not deleted
        Commands.removeGood("hi", "1", goodsArrayList);
        assertEquals(14, goodsArrayList.get(1).getQuantity());

        //test 5, deleting good id that does not exist - fail
        Commands.removeGood("4", "15", goodsArrayList);
        assertEquals(2, goodsArrayList.size());
    }

    //    @Test
    //    void totalGoodsTest(){
    //        ArrayList<Goods> goodsArrayList = new ArrayList<>();
    //        Commands.addGood("1", "chairs", "15", goodsArrayList);
    //        Commands.addGood("2", "table", "15", goodsArrayList);
    //
    //
    //    }
}
