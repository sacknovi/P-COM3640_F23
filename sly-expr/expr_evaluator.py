from expr_lexer import ExprLexer
from expr_parser import ExprParser


if __name__ == "__main__":
    lexer = ExprLexer()
    parser = ExprParser()
    
    while True:
        try:
            text = input("expr > ")
            if text:
                result = parser.parse(lexer.tokenize(text))
                print(result)

        except KeyboardInterrupt:
            break

        except Exception as e:
            print(e)
