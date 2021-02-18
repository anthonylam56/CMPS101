

public class MatrixTest{
        public static void main(String[] args){
                Matrix A;       
                Matrix B;      
                Matrix C;      

                A = new Matrix(3);
                B = new Matrix(3);

                A.changeEntry(1,1,1);
                A.changeEntry(1,2,2);
                A.changeEntry(1,3,3);
                A.changeEntry(2,1,4);
                A.changeEntry(2,2,5);
                A.changeEntry(2,3,6);
                A.changeEntry(3,1,7);
                A.changeEntry(3,2,8);
                A.changeEntry(3,3,9);

                B.changeEntry(1,1,1);
                B.changeEntry(1,2,2);
                B.changeEntry(1,3,3);
                B.changeEntry(2,1,4);
                B.changeEntry(2,2,5);
                B.changeEntry(2,3,6);
                B.changeEntry(3,1,7);
                B.changeEntry(3,2,8);
                B.changeEntry(3,3,0);

                System.out.println("Calling getSize()");
                System.out.println("A: " + A.getSize());
                System.out.println("B: " + B.getSize());

                System.out.println("Calling getNNZ()");
                System.out.println("A: " + A.getNNZ());
                System.out.println("B: " + B.getNNZ());


                System.out.println("Calling makeZero()");
                System.out.println("B after makeZero():\n" + B);


                System.out.println("Calling copy()");
                System.out.println("Copying Matrix A:\n" + A.copy());


                System.out.println("Calling changeEntry");
                A.changeEntry(1,1,0);
                System.out.println("Changing (1,1) of A:\n" + A);


                System.out.println("Calling scalarMult()");
                System.out.println("Calling A.scalarMult(1.5)\n" + A.scalarMult(1.5));

                System.out.println("Calling add()");
                System.out.println("A:\n" + A);
                System.out.println("B:\n" + B);
                System.out.println("A + B: \n" + A.add(B));

                System.out.println("Calling sub()");
                System.out.println("A:\n" + A);
                System.out.println("B:\n" + B);
                System.out.println("A + B: \n" + A.sub(B));

                System.out.println("Calling transpose on A");
                System.out.println("A:\n" + A);
                System.out.println("A transpose:\n" + A.transpose());


                System.out.println("Calling A.mult(B)");
                System.out.println("A:\n" + A);
                System.out.println("B:\n" + B);
                System.out.println("A * B: \n" + A.mult(B));


	}
}
