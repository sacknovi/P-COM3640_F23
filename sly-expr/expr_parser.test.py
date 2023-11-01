from expr_parser import ExprParser
from expr_lexer import ExprLexer

def test_expr_parser():
    lexer = ExprLexer()
    parser = ExprParser()

    # Test addition
    assert parser.parse(lexer.tokenize('1 + 2')) == 3

    # Test subtraction
    assert parser.parse(lexer.tokenize('5 - 3')) == 2
    assert parser.parse(lexer.tokenize('5 - 3 - 2')) == parser.parse(lexer.tokenize('(5 - 3) - 2')) # left associative

    # Test multiplication
    assert parser.parse(lexer.tokenize('2 * 3')) == 6

    # Test division
    assert parser.parse(lexer.tokenize('6 / 3')) == 2
    assert parser.parse(lexer.tokenize('6 / 3 / 2')) == parser.parse(lexer.tokenize('(6 / 3) / 2')) # left associative
    
    # Test unary minus
    assert parser.parse(lexer.tokenize('-2 * 1')) == -2
    assert parser.parse(lexer.tokenize('1 * -2')) == -2

    # Test operation precedence 

    # multiplication has higher precedence than addition
    assert parser.parse(lexer.tokenize('2 + 3 * 4')) == parser.parse(lexer.tokenize('2 + (3 * 4)'))
    assert parser.parse(lexer.tokenize('2 * 3 + 4')) == parser.parse(lexer.tokenize('(2 * 3) + 4'))
    
    # multiplication has higher precedence than subtration
    assert parser.parse(lexer.tokenize('2 - 3 * 4')) == parser.parse(lexer.tokenize('2 - (3 * 4)'))
    assert parser.parse(lexer.tokenize('2 * 3 - 4')) == parser.parse(lexer.tokenize('(2 * 3) - 4'))
 
    # division has higher precedence than addition
    assert parser.parse(lexer.tokenize('2 + 3 / 4')) == parser.parse(lexer.tokenize('2 + (3 / 4)'))
    assert parser.parse(lexer.tokenize('2 / 3 + 4')) == parser.parse(lexer.tokenize('(2 / 3) + 4'))
 
    # division has higher precedence than subraction
    assert parser.parse(lexer.tokenize('2 - 3 / 4')) == parser.parse(lexer.tokenize('2 - (3 / 4)'))
    assert parser.parse(lexer.tokenize('2 / 3 - 4')) == parser.parse(lexer.tokenize('(2 / 3) - 4'))
       
   

test_expr_parser()
print("All tests passed!")