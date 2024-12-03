class Operators {
    public:
        //Method for addition
        double addition(double a, double b) {
            return a + b;
        }
        
        //Method for subtraction
        double subtraction(double a, double b) {
            return a - b;   
        }

        //Method for multiplication
        double multiplication(double a, double b) { 
            return a * b;
        }

        //Method for division
        double division(double a, double b) {
            if (b != 0) {
                return a / b;
            } else {
                return 0;
            }
        }

        //Method for modular
        int modular(int a, int b) {
            if (b > 0) {
                return a % b;    
            } else {
                return -1;
            }
        }
        
        //Method for exponents
        //Takes in two number: first number is the base number the second is the power
        double exponents(double a, double b) {
            int c = a;
            for(int i = 0; i < b; i++){
                c = multiplication(c, a);
            }
            return c;
        }

};