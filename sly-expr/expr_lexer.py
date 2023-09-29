from sly import Lexer

class ExprLexer(Lexer):
    # Set of token names
    tokens = { NUMBER, PLUS, MINUS, TIMES, DIVIDE, LPAREN, RPAREN }

    # Regular expression rules for simple tokens
    PLUS    = r'\+'
    MINUS   = r'-'
    TIMES   = r'\*'
    DIVIDE  = r'/'
    LPAREN  = r'\('
    RPAREN  = r'\)'

    # Regular expression rule with action code
    @_(r'\d+')
    def NUMBER(self, t):
        t.value = int(t.value)
        return t

    # Ignored characters (whitespaces)
    ignore = ' \t'
