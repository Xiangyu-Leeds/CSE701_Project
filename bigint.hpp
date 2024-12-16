/**
 * @file bigint.hpp
 * @brief A header file defining the `bigint` class.
 */

class bigint {
    /**
     * @brief Overloaded stream output operator to print bigint objects.
     * @param out The output stream.
     * @param num The bigint object to print.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &out, const bigint &num){
        if (num.negative) {
            out << '-';
        }
        out << num.number;
        return out;
    }
private:
    std::string number;
    bool negative;
     /**
     * @brief Removes leading zeros from the number string.
     */
    void removeZeros(){
        while(number.size() > 1 && number[0] == '0'){
            number.erase(0, 1);
        }
    }
     /**
     * @brief Validates that a string contains only numeric digits.
     * @param str The string to validate.
     * @param startIndex The starting index to check from.
     * @return True if the string contains only digits, otherwise false.
     */
     bool isValidNumber(const std::string &str, size_t startIndex) const {
        for (size_t i = startIndex; i < str.size(); ++i) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }
        return true;
    }

public:
    /**
     * @brief Default constructor.
     */
    bigint(): number("0"), negative(false) {}
     /**
     * @brief Constructor that takes 64-bit integer.
     * @param num The integer to initialize the bigint.
     */
    bigint(const int64_t num){
        if (num < 0) {
            negative = true;
            number = std::to_string(-num);
        } else {
            negative = false;
            number = std::to_string(num);
        }
       
    }
     /**
     * @brief Constructor that takes a string.
     * @param num A string representing a number.
     */
    bigint(const std::string &num) {
        if (num.empty()) {
            throw std::invalid_argument("Empty string cannot be converted");
        }

        size_t startIndex = 0;
        if (num[0] == '-') {
            negative = true;
            startIndex = 1;
        } else {
            negative = false;
        }

        if (!isValidNumber(num, startIndex)) {
            throw std::invalid_argument("Invalid characters");
        }

        number = num.substr(startIndex);
        removeZeros();
    }
    /**
     * @brief Overloaded addition operator.
     * @param num The bigint to add.
     * @return A new bigint.
     */
    bigint operator+(const bigint &num) const{
      if(negative == num.negative){
        std::string sum;
        int64_t next = 0;
        size_t numberSize = number.size() ;
        size_t numSize = num.number.size();
        int64_t num1 = 0;
        int64_t num2 = 0;
        while(numberSize > 0 || numSize > 0 || next > 0) {
          if(numberSize > 0){
            --numberSize;
            num1 = number[numberSize] - '0';
          } else {
            num1 = 0;
          }
          if(numSize > 0){
            --numSize;
            num2 = num.number[numSize] - '0';
          
          } else {
            num2 = 0;
          }
          int64_t plus = num1 + num2 + next;
          next = plus / 10;
          sum += std::to_string(plus % 10);
        }

        std::reverse(sum.begin(), sum.end());
        bigint resultSum;
        resultSum.number = sum;
        resultSum.negative = negative;
        resultSum.removeZeros();
        if(resultSum.number == "0") {
              resultSum.negative = false;
        }
        return resultSum;
      }else if(negative){
        return num - (-*this);
      }else{
        return *this - (-num);
      }

    }
      /**
     * @brief Overloaded addition assignment operator.
     * @param num The bigint to add.
     * @return A reference to the current bigint.
     */
    bigint& operator+=(const bigint &num){
        *this = *this + num;
        return *this;
    }
    /**
     * @brief Overloaded subtraction operator.
     * @param num The bigint to subtract.
     * @return A new bigint.
     */
    bigint operator-(const bigint &num) const{
        if(number == num.number && negative == num.negative){
            return bigint("0");
        }
        if(negative != num.negative){
            return *this + (-num);
        }
        bigint larger = *this;
        bigint smaller = num;
        int64_t before = 0;
        bool resultNegative = negative;
        if(*this < num){
            larger = num;
            smaller = *this;
            resultNegative = true;
        }else{
            resultNegative = false;
        }
        std::string difference;
        size_t largerSize = larger.number.size();
        size_t smallerSize = smaller.number.size();
        while(largerSize > 0 || smallerSize > 0 || before > 0){
            int64_t num1 = 0;
            int64_t num2 = 0;
            if(largerSize > 0){
                --largerSize;
                num1 = larger.number[largerSize] - '0';
            } else {
                num1 = 0;
            }
            if(smallerSize > 0){
                --smallerSize;
                num2 = smaller.number[smallerSize] - '0';
            } else {
                num2 = 0;
            }
            int64_t minus = num1 - num2 - before;
            if(minus < 0){
                minus += 10;
                before = 1;
            } else {
                before = 0;
            }
            difference += std::to_string(minus);
        }

        std::reverse(difference.begin(), difference.end());

        bigint resultDifference;
        resultDifference.number = difference;
        resultDifference.negative = resultNegative;
        resultDifference.removeZeros();
        if (resultDifference.number == "0") {
            resultDifference.negative = false;
        }


        return resultDifference;
    }
     /**
     * @brief Overloaded subtraction assignment operator.
     * @param num The bigint to subtract.
     * @return A reference to the current bigint after subtraction.
     */
    bigint operator-=(const bigint &num){
        *this = *this - num;
        return *this;
    }
     /**
     * @brief Overloaded multiplication operator.
     * @param num The bigint to multiply with.
     * @return A new bigint.
     */
    bigint operator*(const bigint &num) const{
        if(number == "0" || num.number == "0"){
            return bigint("0");
        }
        size_t size = number.size() + num.number.size();
        std::string res(size, '0');

        for(std::size_t i = number.size(); i > 0; --i){
            int64_t next = 0;
            for(std::size_t j = num.number.size(); j > 0; --j){
                int64_t mul = (number[i-1] - '0') * (num.number[j-1] - '0') + (res[i + j - 1] - '0') + next;
                res[i + j - 1] = mul % 10 + '0';
                next = mul / 10;
            }
            res[i-1] += next;
            }
            while(res.size() > 1 && res[0] == '0'){
                res.erase(0, 1);
            }
            bigint resultMul;
            resultMul.number = res;
            if(negative != num.negative){
                resultMul.negative = true;
            } else {
                resultMul.negative = false;
            }
            return resultMul;
    }
    /**
     * @brief Overloaded multiplication assignment operator.
     * @param num The bigint to multiply with.
     * @return A reference to the current bigint after multiplication.
     */
    bigint operator*=(const bigint &num){
        *this = *this * num;
        return *this;
    }
      /**
     * @brief Unary negation operator.
     * @return A new bigint representing the negated value.
     */

    bigint operator-() const{
        bigint res = *this;
        if(res.number != "0"){
            res.negative = !res.negative;
        }
        if (res.number == "0") {
            res.negative = false;
        }
        return res;
    }
    /**
     * @brief Overloaded equality comparison operator.
     * @param num The bigint to compare with.
     * @return True if both bigints are equal, otherwise false.
     */

    bool operator==(const bigint &num) const{
        if(number == num.number && negative == num.negative){
            return true;
        }else{
            return false;
        }
    }
      /**
     * @brief Overloaded inequality comparison operator.
     * @param num The bigint to compare with.
     * @return True if both bigints are not equal.
     */
    bool operator!=(const bigint &num) const{
        if(*this==num){
            return false;
        }else{
            return true;
        }
    }
     /**
     * @brief Overloaded less-than comparison operator.
     * @param num The bigint to compare with.
     * @return True if the current bigint is less than the other.
     */
    bool operator<(const bigint &num) const {
        if (negative && !num.negative) {
            return true;
        } else if (!negative && num.negative) {
            return false;
        }

        bool resultNegative = negative;

        if (number.size() != num.number.size()) {
            if (resultNegative) {
                if (number.size()>num.number.size()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                if (number.size() < num.number.size()) {
                    return true;
                } else {
                    return false;
                }
            }
        }

        for (std::size_t i = 0; i < number.size(); ++i) {
            if (number[i] != num.number[i]) {
                if (resultNegative) {
                    if(number[i] > num.number[i]){
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (number[i] < num.number[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
        return false;
    }

    /**
     * @brief Overloaded greater-than comparison operator.
     * @param num The bigint to compare with.
     * @return True if the current bigint is greater than the other.
     */
    bool operator>(const bigint &num) const{
        if(*this < num || *this == num){
            return false;
        }else{
            return true;
        }
    }
     /**
     * @brief Overloaded less-than-or-equal comparison operator.
     * @param num The bigint to compare with.
     * @return True if the current bigint is less than or equal to the other.
     */
    bool operator<=(const bigint &num) const{
        if(*this < num || *this == num){
            return true;
        }else{
            return false;
        }
    }
     /**
     * @brief Overloaded greater-than-or-equal comparison operator.
     * @param num The bigint to compare with.
     * @return True if the current bigint is greater than or equal to the other.
     */
    bool operator>=(const bigint &num) const{
        if(*this > num || *this == num){
            return true;
        }else{
            return false;
        }
    }
     /**
     * @brief Pre-increment operator.
     * @return A reference to the incremented bigint.
     */
    bigint &operator++(){
        *this = *this + 1;
        return *this;
    }
      /**
     * @brief Post-increment operator.
     * @return The bigint before incrementing.
     */
    bigint operator++(int){
        bigint res = *this;
        *this = *this + 1;
        return res;
    }
     /**
     * @brief Pre-decrement operator.
     * @return A reference to the decremented bigint.
     */
    bigint &operator--(){
        *this = *this - 1;
        return *this;
    }
    /**
     * @brief Post-decrement operator.
     * @return The bigint before decrementing.
     */
    bigint operator--(int){
        bigint res = *this;
        *this = *this - 1;
        return res;
    }


};










