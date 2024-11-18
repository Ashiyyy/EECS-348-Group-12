class Operators {
    public:
        //Method for addition
        int addition(int a, int b) {
            return a + b;
        }
        
        //Method for subtraction
        int subtraction(int a, int b) {
            return a - b;   
        }

        //Method for multiplication
        int multiplication(int a, int b) { 
            return a * b;
        }

        //Method for division
        int division(int a, int b) {
            return a / b;
        }

        //Method for modular
        int modular(int a, int b) {
            return a % b;
        }
        
        //Method for exponents
        //Takes in two number: first number is the base number the second is the power
        int exponents(int a, int b) {
            int c = a;
            for(int i = 0; i < b; i++){
                c = multiplication(c, a);
            };
            return c;
        }

};