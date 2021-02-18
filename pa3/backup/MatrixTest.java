

public class MatrixTest{
	public static void main(String[] args){
		Matrix A;
		Matrix B;
		Matrix C;

		A = new Matrix(10);
        B = new Matrix(10);
        A.changeEntry(1, 1, 4);
        A.changeEntry(1, 2, 2);
        A.changeEntry(1, 3, 0);
        A.changeEntry(2, 1, 2);
        A.changeEntry(3, 1, 0);
        A.changeEntry(2, 2, 2);
        A.changeEntry(3, 3, 0);
        C = A.add(A);
        //if (C.getNNZ() != 4 || A.getNNZ() != 4) return 1;
        B.changeEntry(1, 1, -4);
        B.changeEntry(1, 2, 0);
        B.changeEntry(2, 1, 0);
        B.changeEntry(2, 2, -2);
        B.changeEntry(2, 4, 2);
        B.changeEntry(3, 1, 0);
        B.changeEntry(3, 2, 2);
        B.changeEntry(7, 8, 5);
        C = A.add(B);
        System.out.println(A);
        System.out.println(B);
        System.out.println(C);
        System.out.println(C.getNNZ());
        //if (C.getNNZ() != 5) return 2;

		/*A = new Matrix(10);
        B = new Matrix(10);
        A.changeEntry(1, 1, -4);
        A.changeEntry(1, 2, -2);
        A.changeEntry(1, 3, 0);
        A.changeEntry(2, 5, 4);
        A.changeEntry(2, 1, -2);
        A.changeEntry(3, 1, 2);
        A.changeEntry(2, 2, -2);
        A.changeEntry(3, 3, 0);
        C = A.sub(A);
        if (C.getNNZ() != 0 || A.getNNZ() != 6) return 1;
        B.changeEntry(1, 1, -4);
        B.changeEntry(1, 2, 0);
        B.changeEntry(2, 1, 0);
        B.changeEntry(2, 2, -2);
        B.changeEntry(2, 4, 2);
        B.changeEntry(3, 1, 2);
        B.changeEntry(3, 2, 2);
        B.changeEntry(7, 8, 5);
        C = A.sub(B);

        if (C.getNNZ() != 6) return 2;*/
	}
}
