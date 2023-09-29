from sly import Parser

from expr_lexer import ExprLexer

class ExprParser(Parser):
    tokens = ExprLexer.tokens

    precedence = (
        ('left', PLUS, MINUS),
        ('left', TIMES, DIVIDE),
        ('right', POWER),  # Right-associative (e.g., 2^3^2 is 2^(3^2))
        ('nonassoc', 'UMINUS'),
    )

    def __init__(self):
        self.names = {}

    @_('expr PLUS expr')
    def expr(self, p):
        return p.expr0 + p.expr1

    @_('expr MINUS expr')
    def expr(self, p):
        return p.expr0 - p.expr1

    @_('expr TIMES expr')
    def expr(self, p):
        return p.expr0 * p.expr1

    @_('expr DIVIDE expr')
    def expr(self, p):
        return p.expr0 / p.expr1

    @_('MINUS expr %prec UMINUS')
    def expr(self, p):
        return -p.expr

    @_('LPAREN expr RPAREN')
    def expr(self, p):
        return p.expr

    @_('NUMBER')
    def expr(self, p):
        return p.NUMBER
    
    @_('QUIT')
    def expr(self, p):
        print("Exiting the program...")
        exit(0)
        
    @_('expr MODULO expr')
    def expr(self, p):
        return p.expr0 % p.expr1
        
    @_('expr POWER expr')
    def expr(self, p):
        return p.expr0 ** p.expr1
