# dsa_hw3-4_Palindrome
Minimum characters to be added at front to make string palindrome

演算法參考(https://www.geeksforgeeks.org/minimum-characters-added-front-make-string-palindrome/) </br>
一開始會TLE,所以必須用KMP演算法,不能用一般的暴力解.我是使用陣列去取代c++的vector. </br>
之後會一直有一題吃WA,這是因為Array最後一個位置必須要放'\0'這個結束符號(大小一格). </br>
舉例,"hello",strlen()只會看到hello,所以輸出5,但是malloc時,這樣就會少了'\0'這個位置,導致WA,所以必須多加+1才行. </br>
還有for loop的條件不能放strlen(s),要先宣告變數去存strlen的值,不然每次去跑迴圈都會算一次O(n)的strlen.
