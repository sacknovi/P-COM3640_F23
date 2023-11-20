import pytest
from expr_parser import ExprParser
from expr_lexer import ExprLexer

# Initialize the lexer and parser
lexer = ExprLexer()
parser = ExprParser()

def value(expr):
    tokens = lexer.tokenize(expr)
    return parser.parse(tokens)


def test_exsiting_functionality_intact():
    # Test addition
    assert value("1 + 2") == 3

    # Test subtraction
    assert value("5 - 3") == 2
    assert value("5 - 3 - 2") == value("(5 - 3) - 2")  # left associative

    # Test multiplication
    assert value("2 * 3") == 6

    # Test division
    assert value("6 / 3") == 2
    assert value("6 / 3 / 2") == value("(6 / 3) / 2")  # left associative

    # Test unary minus
    assert value("-2 * 1") == -2
    assert value("1 * -2") == -2

    # multiplication has higher precedence than addition
    assert value("2 + 3 * 4") == value("2 + (3 * 4)")
    assert value("2 * 3 + 4") == value("(2 * 3) + 4")

    # multiplication has higher precedence than subtration
    assert value("2 - 3 * 4") == value("2 - (3 * 4)")
    assert value("2 * 3 - 4") == value("(2 * 3) - 4")

    # division has higher precedence than addition
    assert value("2 + 3 / 4") == value("2 + (3 / 4)")
    assert value("2 / 3 + 4") == value("(2 / 3) + 4")

    # division has higher precedence than subraction
    assert value("2 - 3 / 4") == value("2 - (3 / 4)")
    assert value("2 / 3 - 4") == value("(2 / 3) - 4")


@pytest.mark.parametrize("op", ["%"])
def test_modulo(op):
    assert value(f"10 {op} 13") == 10
    assert value(f"20 {op} 13") == 7


@pytest.mark.parametrize("op, associativity", [("%", "left")])
def test_modulo_associativity(op, associativity):
    if associativity == "left":
        assert value(f"20 {op} 13 {op} 4") == value(f"(20 {op} 13) {op} 4")
    else:
        assert value(f"20 {op} 13 {op} 4") == value(f"20 {op} (13 {op} 4)")
        
      
@pytest.mark.parametrize("op", ["%"])
def test_modula_precedence_higher_than_addsub(op):
    assert value(f"20 {op} 13 + 4") == value(f"(20 {op} 13) + 4")
    assert value(f"20 + 13 {op} 4") == value(f"20 + (13 {op} 4)")
    assert value(f"20 {op} 13 - 4") == value(f"(20 {op} 13) - 4")
    assert value(f"20 - 13 {op} 4") == value(f"20 - (13 {op} 4)")


@pytest.mark.parametrize("op", ["%"])
def test_modula_precedence_same_as_muldiv(op):
    assert value(f"20 {op} 13 * 4") == value(f"(20 {op} 13) * 4")
    assert value(f"20 * 13 {op} 4") == value(f"(20 * 13) {op} 4")
    assert value(f"20 {op} 13 / 4") == value(f"(20 {op} 13) / 4")
    assert value(f"20 / 13 {op} 4") == value(f"(20 / 13) {op} 4")


@pytest.mark.parametrize("op", ["^"])
def test_power(op):
    assert value(f"2 {op} 3") == 8
    assert value(f"3 {op} 2") == 9
    assert value(f"2 {op} 2 {op} 2") == 16


@pytest.mark.parametrize("op, associativity", [("^", "right")])
def test_power_associativity(op, associativity):
    if associativity == "left":
        assert value(f"2 {op} 3 {op} 2") == value(f"(2 {op} 3) {op} 2")
    else:
        assert value(f"2 {op} 3 {op} 2") == value(f"2 {op} (3 {op} 2)")
  
        
@pytest.mark.parametrize("op", ["^"])
def test_power_precedence_higher_than_mul(op): # and therefore hgher than all
    assert value(f"20 {op} 13 * 4") == value(f"(20 {op} 13) * 4")
    assert value(f"20 * 13 {op} 4") == value(f"20 * (13 {op} 4)")
    
    
def test_in_one():
    assert value("1 in (1)")
    assert not value("1 in (2)")
    
    
def test_in_multiple():
    assert value("4 in (1,2,3,4,5)")
    assert not value("1 in (2,3,4,5)")
    
    
def test_in_expr_values():
    assert value("1 in (5-4)")
    assert not value("1 in (5-3)")


def test_in_with_expr():
    assert value("(1+2) in (3)")
    assert not value("(1+3) in (3)")

    
def test_in_lowest_precedence():
    assert value("1+3 in (3)")

        
