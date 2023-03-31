#include <arithmetica.hpp>
#include <basic_math_operations.hpp>
#include <iostream>
#include <random>
#include <regex>
#include <string>

typedef basic_math_operations::BMONum bmo_num;
typedef arithmetica::Fraction am_frac;

class ICSEQuestionGenerator {
protected:
  int grade;
  // A variable that stores the question type.
  int type;
  unsigned long long max_decimal_places = 2;

public:
  ICSEQuestionGenerator(int grade) : grade(grade) {}
  virtual class ICSEQuestion *generateQuestion() = 0;
  // An enum of valid question types.
  enum QuestionType {
    EXAMINE_ROOTS,
    FIND_COEFFICIENTS_QUADRATIC,
    SIMPLE_QUADRATIC_FACTORABLE,
    TEDIOUS_QUADRATIC_FACTORABLE
  };
  // Functions to get and set the question type.
  QuestionType getQuestionType() { return static_cast<QuestionType>(type); }
  void setQuestionType(QuestionType type) { this->type = type; }
  // Function to set the maximum number of decimal places.
  void setMaxDecimalPlaces(unsigned long long max_decimal_places) {
    this->max_decimal_places = max_decimal_places;
  }
  unsigned long long getMaxDecimalPlaces() { return max_decimal_places; }
};

class ICSEQuestion {
protected:
  std::string question, answer;

public:
  virtual std::string getQuestion() = 0;
  virtual std::string getAnswer() = 0;
};

class ICSEMathQuestion : public ICSEQuestion {
public:
  virtual ICSEQuestionGenerator::QuestionType getType() = 0;
};

class ExamineRootsQuestion : public ICSEMathQuestion {
protected:
  bmo_num a, b, c;

public:
  ExamineRootsQuestion(unsigned long long max_decimal_places) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_one_in_three(1, 3);
    std::uniform_int_distribution<> dis_one_in_two(0, 1);
    std::uniform_int_distribution<> dis_no_digits(1, max_decimal_places);

    // Cases:
    // Real:
    // - Rational
    //  - Equal
    //  - Unequal
    // - Irrational
    //  - Unequal
    // Complex

    // Let's bias towards real roots, with a 1/3 chance of complex roots.
    int case_num = dis_one_in_three(gen);
    if (case_num == 1) {
      // Yes, a is 1, on purpose.
      // roots: random + random * i and random - random * i
      // let's say the random numbers are p,q
      // roots: p + qi and p - qi
      // equation: (x - p - qi) * (x - p + qi) = 0
      //       ==> (x - p)^2 + q^2 = 0
      //       ==> x^2 - 2px + (p^2 + q^2) = 0
      bmo_num p = basic_math_operations::random(dis_no_digits(gen));
      bmo_num q = basic_math_operations::random(dis_no_digits(gen));
      a = "1";
      b = p * "-2";
      c = p * p + q * q;

      // Form the answer.
      answer = "Complex.";
    } else {
      if (dis_one_in_two(gen)) {
        // rational
        if (dis_one_in_two(gen)) {
          // unequal
          // roots: random/random and random/random
          // random numbers: p,q,r where r != 0
          // roots: p/r and q/r
          // equation: (rx - p) * (rx - q) = 0
          //       ==> (r^2)x^2 - q rx - p rx + pq = 0
          //       ==> (r^2)x^2 - (p + q)r x + pq = 0
          bmo_num p = basic_math_operations::random(dis_no_digits(gen));
          bmo_num q = basic_math_operations::random(dis_no_digits(gen));
          bmo_num r = basic_math_operations::random(dis_no_digits(gen));
          while (r == "0") {
            r = basic_math_operations::random(dis_no_digits(gen));
          }
          a = r * r;
          b = (p + q) * r * "-1";
          c = p * q;
          answer = "Rational and unequal.";
        } else {
          // equal
          // roots: random/random and random/random
          // random numbers: p,q where p != 0, q != 0
          // roots: p/q and p/q
          // equation: (px - q)^2 = 0
          //       ==> (p^2)x^2 - 2pqx + q^2 = 0
          bmo_num p = basic_math_operations::random(dis_no_digits(gen));
          bmo_num q = basic_math_operations::random(dis_no_digits(gen));
          while ((p - "0") == "0") {
            p = basic_math_operations::random(dis_no_digits(gen));
          }
          while ((q - "0") == "0") {
            q = basic_math_operations::random(dis_no_digits(gen));
          }
          a = p * p;
          b = p * q * "-2";
          c = q * q;
          answer = "Rational and equal.";
        }
      } else {
        // irrational unequal
        // roots: (p+sqrt(q))/r, (p-sqrt(q))/r where q != 0 and r != 0
        // random numbers: p,q,r
        // equation: (rx - p - sqrt(q)) * (rx - p + sqrt(q)) = 0
        //      ==> r^2 x^2 - 2prx + p^2 - q = 0
        bmo_num p = basic_math_operations::random(dis_no_digits(gen));
        bmo_num q = basic_math_operations::random(dis_no_digits(gen));
        bmo_num r = basic_math_operations::random(dis_no_digits(gen));
        while ((q - "0") == "0") {
          q = basic_math_operations::random(dis_no_digits(gen));
        }
        while ((r - "0") == "0") {
          r = basic_math_operations::random(dis_no_digits(gen));
        }
        a = r * r;
        b = p * r * "-2";
        c = p * p - q;
        answer = "Irrational and unequal.";
      }
    }

    // Form the question.
    question += a.number + "x^2 + " + b.number + "x + " + c.number + " = 0.";

    std::vector<std::string> q_variations = {
        "Without solving, find the nature of roots of the equation ",
        "Find the nature of the roots of the following equation without "
        "solving it: ",
        "What is the nature of the roots of the following equation? Do not "
        "solve it: ",
        "Determine the nature of the roots of the following equation without "
        "solving it: ",
        "Without solving, determine the nature of the roots of the following "
        "equation: ",
    };

    std::uniform_int_distribution<int> dis_q_variations(0, q_variations.size() -
                                                               1);
    question = q_variations[dis_q_variations(gen)] + question;
  }
  std::string getQuestion() override { return question; }
  std::string getAnswer() override { return answer; }
  ICSEQuestionGenerator::QuestionType getType() override {
    return ICSEQuestionGenerator::EXAMINE_ROOTS;
  }
};

class FindCoefficientsQuadraticQuestion : public ICSEMathQuestion {
protected:
  bmo_num a, b, c, d, e, p, q, n;

public:
  // Find the value of 'n' such that the roots of the equation (an + b)x^2 + (cn
  // + d)x + e = 0 are equal.
  FindCoefficientsQuadraticQuestion(unsigned long long max_decimal_places) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_no_digits(1, max_decimal_places);

    a = basic_math_operations::random(dis_no_digits(gen));
    c = basic_math_operations::random(dis_no_digits(gen));

    p = basic_math_operations::random(dis_no_digits(gen));
    q = basic_math_operations::random(dis_no_digits(gen));
    e = q * q;
    q = q * "-2" * p;
    p = p * p;

    n = basic_math_operations::random(dis_no_digits(gen));

    // an + b = p ==> b = p - an
    // cn + d = q ==> d = q - cn

    b = p - a * n;
    d = q - c * n;

    std::vector<std::pair<std::string, std::string>> question_variations = {
        {"Find the value of [var] such that the roots of the equation ",
         " are equal."},
        {"Assuming that the following equation has equal roots, find the value "
         "of [var]: ",
         ""},
        {"The equation ", " has equal roots. Find the value of [var]."},
        {"Find the value of [var] for which the equation ",
         " has equal roots."},
        {"For which value of [var] does the equation ", " have equal roots?"}};

    std::uniform_int_distribution<int> dis_q_variations(
        0, question_variations.size() - 1);
    std::pair<std::string, std::string> q_variation =
        question_variations[dis_q_variations(gen)];

    // Replace [var] with some random letter from a to z excluding 'x'.
    question = q_variation.first + "(" + a.number + "[var] + " + b.number +
               ")x^2 + (" + c.number + "[var] + " + d.number + ")x + " +
               e.number + " = 0" + q_variation.second;
    std::uniform_int_distribution<int> dis_var(0, 25);
    char var = 'a' + dis_var(gen);
    while (var == 'x') {
      var = 'a' + dis_var(gen);
    }
    question = std::regex_replace(question, std::regex("\\[var\\]"),
                                  std::string(1, var));

    answer = n.number;
  }

  // getType
  ICSEQuestionGenerator::QuestionType getType() override {
    return ICSEQuestionGenerator::FIND_COEFFICIENTS_QUADRATIC;
  }
  // getQuestion
  std::string getQuestion() override { return question; }
  // getAnswer
  std::string getAnswer() override { return answer; }
};

class SimpleQuadraticFactorableQuestion : public ICSEMathQuestion {
protected:
  bmo_num a, b, c;

public:
  SimpleQuadraticFactorableQuestion(unsigned long long max_decimal_places) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_no_digits(1, max_decimal_places);

    // equation: (px - q)(rx - s) = 0
    //       ==> pr x^2 - (ps + qr) x + qs = 0, where p != 0, r != 0

    bmo_num p, q, r, s;
    p = basic_math_operations::random(dis_no_digits(gen));
    q = basic_math_operations::random(dis_no_digits(gen));
    r = basic_math_operations::random(dis_no_digits(gen));
    s = basic_math_operations::random(dis_no_digits(gen));
    while ((p - "0") == "0") {
      p = basic_math_operations::random(dis_no_digits(gen));
    }
    while ((r - "0") == "0") {
      r = basic_math_operations::random(dis_no_digits(gen));
    }
    // If q and s are 0, then re-roll them once (since it's a product, the
    // chances that the overall equation's last term becomes 0 is doubled)
    if ((q - "0") == "0") {
      q = basic_math_operations::random(dis_no_digits(gen));
    }
    if ((s - "0") == "0") {
      s = basic_math_operations::random(dis_no_digits(gen));
    }

    a = p * r;
    b = p * s + q * r;
    c = q * s;

    std::vector<std::pair<std::string, std::string>> question_variations = {
        {"Solve the following equation: ", " = 0"},
        {"Find the roots of the following quadratic function: ", ""},
        {"What is the value(s) of x if ", " = 0"},
        {"Find the value(s) of x such that ", " = 0"},
        {"Find the solution set of the following equation: ", " = 0"}};

    std::uniform_int_distribution<int> dis_q_variations(
        0, question_variations.size() - 1);
    size_t q_index = dis_q_variations(gen);
    std::pair<std::string, std::string> q_variation =
        question_variations[q_index];
    question = q_variation.first + a.number + "x^2 + " + b.number + "x + " +
               c.number + q_variation.second;

    arithmetica::Fraction f1(q.number + "/" +
                             p.number); // to reduce the fraction
    arithmetica::Fraction f2(s.number + "/" + r.number);
    answer =
        "x = " + arithmetica::to_string(f1) + ", " + arithmetica::to_string(f2);
    if (q_index == 4) {
      answer = "x = {(" + arithmetica::to_string(f1) + ", " + arithmetica::to_string(f2) + ")}";
    } else {
      answer =
        "x = " + arithmetica::to_string(f1) + ", " + arithmetica::to_string(f2);
    }
  }
  ICSEQuestionGenerator::QuestionType getType() override {
    return ICSEQuestionGenerator::SIMPLE_QUADRATIC_FACTORABLE;
  }
  std::string getQuestion() override { return question; }
  std::string getAnswer() override { return answer; }
};

class TediousQuadraticFactorableQuestion : public ICSEMathQuestion {
protected:
  am_frac a, b, c, d, e, f, g, h, c_1, c_2, c_3, p, q, t;

public:
  TediousQuadraticFactorableQuestion(unsigned long long max_decimal_places) {
    // I've done a bunch of math to generate a quadratic equation
    // of the form (ax+b)/(cx+d) = (ex+f)/(gx+h) that has the same roots as the
    // equation c_1 x^2 + c_2 x + c_3 = 0

    // (For those who are interested, cross multiply and match coefficients (x^2,
    // x and the constant term)).

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_no_digits(1, max_decimal_places);

    // First generate the simple quadratic equation.
    // Since I don't support torture, I'm gonna let the roots of this equation
    // be good old integers. f(x) = (x - p)(x - q), roots are p and q
    //    ==> x^2 - (p + q) x + pq = 0

    p = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    q = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);

    while (p == "0") {
      p = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    }
    while (q == "0") {
      q = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    }

    c_1 = "1";
    c_2 = (p + q) * "-1";
    c_3 = p * q;

    // Derived from the math mentioned above.
    a = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    b = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    c = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    d = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    e = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);

    while (a == "0") {
      a = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
    }

    g = (c * e + c_1) / a;
    t = b * g - d * e - c_2;

    am_frac denom = b * c - a * d;

    while (denom == "0") {
      c = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
      d = am_frac(basic_math_operations::random(dis_no_digits(gen)).number);
      g = (c * e + c_1) / a;
      t = b * g - d * e - c_2;
      denom = b * c - a * d;
    }

    f = (c_3 * a + b * t) / denom;
    h = (c_3 * c + d * t) / denom;

    std::vector<std::pair<std::string, std::string>> question_variations = {
        {"Solve the following equation: ", ""},
        {"Find the solutions of the following quadratic equation: ", ""},
        {"What is the value(s) of x if ", ""},
        {"Find the value(s) of x such that ", ""},
        {"Find the solution set of the following equation: ", ""}};

    std::uniform_int_distribution<int> dis_q_variations(
        0, question_variations.size() - 1);
    size_t q_index = dis_q_variations(gen);
    std::pair<std::string, std::string> q_variation =
        question_variations[q_index];
    question = q_variation.first + "(" + arithmetica::to_string(a) + "x + " +
               arithmetica::to_string(b) + ")/(" + arithmetica::to_string(c) +
               "x + " + arithmetica::to_string(d) + ") = (" +
               arithmetica::to_string(e) + "x + " + arithmetica::to_string(f) +
               ")/(" + arithmetica::to_string(g) + "x + " +
               arithmetica::to_string(h) + ")" + q_variation.second;
    if (q_index == 4) {
      answer = "x = {(" + arithmetica::to_string(p) + ", " + arithmetica::to_string(q) + ")}";
    } else {
      answer =
        "x = " + arithmetica::to_string(p) + ", " + arithmetica::to_string(q);
    }
  }

  ICSEQuestionGenerator::QuestionType getType() override {
    return ICSEQuestionGenerator::TEDIOUS_QUADRATIC_FACTORABLE;
  }
  std::string getQuestion() override { return question; }
  std::string getAnswer() override { return answer; }
};

class ICSEMathQuestionGenerator : public ICSEQuestionGenerator {
public:
  ICSEMathQuestionGenerator(int grade) : ICSEQuestionGenerator(grade) {}
  ICSEQuestion *generateQuestion() override {
    switch (type) {
    case EXAMINE_ROOTS:
      return new ExamineRootsQuestion(max_decimal_places);
    case FIND_COEFFICIENTS_QUADRATIC:
      return new FindCoefficientsQuadraticQuestion(max_decimal_places);
    case SIMPLE_QUADRATIC_FACTORABLE:
      return new SimpleQuadraticFactorableQuestion(max_decimal_places);
    case TEDIOUS_QUADRATIC_FACTORABLE:
      return new TediousQuadraticFactorableQuestion(max_decimal_places);
    default:
      return nullptr;
    }
  }
};

int main() {
  ICSEQuestionGenerator *gen = new ICSEMathQuestionGenerator(10);
  gen->setMaxDecimalPlaces(1);
  gen->setQuestionType(ICSEQuestionGenerator::TEDIOUS_QUADRATIC_FACTORABLE);
  for (int i = 0;i<10; i++) {
    ICSEQuestion *question = gen->generateQuestion();
    if (question == NULL) {
      std::cerr << "Error: Question generation failed." << std::endl;
      break;
    }
    std::cout << i << ") " << question->getQuestion() << std::endl;
    std::cout << "A: " << question->getAnswer() << std::endl;
    delete question;
  }
  delete gen;
  return 0;
}