#include <iostream>
#include <fstream>


using namespace std;
 
struct Term {
    int coefficient;  // 系数
    int exponent;     // 指数
    Term* next;       // 下一个项的指针
};

void insertTerm(Term*& head, int coeff, int expo) {
    Term* newTerm = new Term;
    newTerm->coefficient = coeff;
    newTerm->exponent = expo;
    newTerm->next = nullptr;

    if (head == nullptr) {
        head = newTerm;
    }
    else {
        Term* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTerm;
    }
}

void destroyPolynomial(Term* head) {
    while (head != nullptr) {
        Term* temp = head;
        head = head->next;
        delete temp;
    }
}

void printPolynomial(Term* head) {
    Term* current = head;
    bool isFirstTerm = true;

    while (current != nullptr) {
        int coeff = current->coefficient;
        int expo = current->exponent;

        if (isFirstTerm) {
            if (coeff < 0)
                cout << "-";
            isFirstTerm = false;
        }
        else {
            if (coeff < 0)
                cout << " - ";
            else
                cout << " + ";
        }

        coeff = abs(coeff);

        if (coeff != 1 || expo == 0)
            cout << coeff;

        if (expo > 0) {
            cout << "x";
            if (expo > 1)
                cout << "^" << expo;
        }

        current = current->next;
    }

    cout << endl;
}

int getHighestExponent(Term* head) {
    int highestExpo = 0;
    Term* current = head;
    while (current != nullptr) {
        if (current->exponent > highestExpo)
            highestExpo = current->exponent;
        current = current->next;
    }
    return highestExpo;
}

Term* simplifyPolynomial(Term* poly) {
    Term* simplifiedPoly = nullptr;
    Term* current = poly;

    while (current != nullptr) {
        if (current->coefficient != 0)
            insertTerm(simplifiedPoly, current->coefficient, current->exponent);
        current = current->next;
    }

    return simplifiedPoly;
}

Term* addPolynomials(Term* poly1, Term* poly2) {
    Term* result = nullptr;
    Term* current = nullptr;

    int highestExponent = max(getHighestExponent(poly1), getHighestExponent(poly2));

    for (int expo = highestExponent; expo >= 0; expo--) {
        int coeff = 0;

        Term* term1 = poly1;
        while (term1 != nullptr) {
            if (term1->exponent == expo)
                coeff += term1->coefficient;
            term1 = term1->next;
        }

        Term* term2 = poly2;
        while (term2 != nullptr) {
            if (term2->exponent == expo)
                coeff += term2->coefficient;
            term2 = term2->next;
        }

        if (coeff != 0)
            insertTerm(result, coeff, expo);

        if (current == nullptr)
            current = result;
    }

    return simplifyPolynomial(result);
}
Term* subtractPolynomials(Term* poly1, Term* poly2) {
    Term* result = nullptr;
    Term* current = nullptr;

    int highestExponent = max(getHighestExponent(poly1), getHighestExponent(poly2));

    for (int expo = highestExponent; expo >= 0; expo--) {
        int coeff = 0;

        Term* term1 = poly1;
        while (term1 != nullptr) {
            if (term1->exponent == expo)
                coeff += term1->coefficient;
            term1 = term1->next;
        }

        Term* term2 = poly2;
        while (term2 != nullptr) {
            if (term2->exponent == expo)
                coeff -= term2->coefficient;
            term2 = term2->next;
        }

        if (coeff != 0)
            insertTerm(result, coeff, expo);

        if (current == nullptr)
            current = result;
    }

    return simplifyPolynomial(result);
}
void savePolynomialsToFile(Term* head, const string& filename)
{
    Term* current = head;
    bool isFirstTerm = true;
    ofstream file(filename);
    while (current != nullptr) {
        int coeff = current->coefficient;
        int expo = current->exponent;

        if (isFirstTerm) {
            if (coeff < 0)
                file << "-";
            isFirstTerm = false;
        }
        else {
            if (coeff < 0)
                file << " - ";
            else
                file << " + ";
        }

        coeff = abs(coeff);

        if (coeff != 1 || expo == 0)
            file << coeff;

        if (expo > 0) {
            file << "x";
            if (expo > 1)
                file << "^" << expo;
        }

        current = current->next;
    }

    file << endl;
}

int main()
{
    Term* poly1 = nullptr;
    int coeff, expo;

    int poly1_termNums, poly2_termNums;      //多项式1和多项式2的项数
    cin >> poly1_termNums >> poly2_termNums;    //输入多项式1和多项式2的项数

    while (poly1_termNums--)
    {
        cin >> coeff >> expo;
        insertTerm(poly1, coeff, expo); //多项式1插入节点
    }
    savePolynomialsToFile(poly1, "poly1.txt");   //保存多项式1至poly1.txt


    Term* poly2 = nullptr;
    while (poly2_termNums--)
    {
        cin >> coeff >> expo;
        insertTerm(poly2, coeff, expo);
    }
    savePolynomialsToFile(poly2, "poly2.txt");

    cout << "多项式1: ";
    printPolynomial(poly1);

    cout << "多项式2: ";
    printPolynomial(poly2);

    Term* sum = addPolynomials(poly1, poly2);   //计算两个多项式的和
    cout << "相加结果: ";
    printPolynomial(sum);

    Term* diff = subtractPolynomials(poly1, poly2);     //计算两个多项式的差
    cout << "相减结果: ";
    printPolynomial(diff);

    destroyPolynomial(poly1);   //内存管理
    destroyPolynomial(poly2);
    destroyPolynomial(sum);
    destroyPolynomial(diff);

    return 0;
}
