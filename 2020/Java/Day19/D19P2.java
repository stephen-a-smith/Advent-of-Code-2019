package Day19;

import java.io.File;

import aocutil.Utilities;

public class D19P2 {
  public static void main(String[] args) {
    Checker checker = new Checker(Utilities.parseInputFile(new File(args[0])));
    checker.part2();
    System.out.printf("The number of matches is %d%n", checker.check(0));
  }
}
