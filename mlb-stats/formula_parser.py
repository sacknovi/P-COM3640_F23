from formula_lexer import CalcLexer
from sly import Parser


class CalcParser(Parser):
    tokens = CalcLexer.tokens

    precedence = (
        ('left', 'AND', 'OR'),
        ('nonassoc', 'LT', 'GT', 'LE', 'GE', 'EQ', 'NE'),
        ("left", PLUS, MINUS),
        ("left", TIMES, DIVIDE),
        ("nonassoc", "UMINUS"),
    )

    def __init__(self, env: dict):
        self.env = env

    def parse(self, key):
        result_or_tokens = self.env.get(key)
        if result_or_tokens is None:
            raise KeyError(f"Formula {key} not found in environment")
        result = super().parse(result_or_tokens)
        self.env[key] = result
        return result

    @_("expr")
    def statement(self, p):
        return p.expr

    @_("expr PLUS expr", 
       "expr MINUS expr", 
       "expr TIMES expr", 
       "expr DIVIDE expr"
    )
    def expr(self, p):
        # Type checking: Ensure both expressions are of the same type
        if type(p.expr0) != type(p.expr1):
            raise TypeError(
                f"Type mismatch: {type(p.expr0).__name__} and {type(p.expr1).__name__}"
            )

        if p[1] == "+":
            return p.expr0 + p.expr1
        elif p[1] == "-":
            return p.expr0 - p.expr1
        elif p[1] == "*":
            return p.expr0 * p.expr1
        elif p[1] == "/":
            return p.expr0 / p.expr1

    @_("MINUS expr %prec UMINUS")
    def expr(self, p):
        return -p.expr

    @_('IF "(" expr "," expr "," expr ")"')
    def expr(self, p):
        return p.expr1 if p.expr0 else p.expr2

    @_('"(" expr ")"')
    def expr(self, p):
        return p.expr

    @_('NOT "(" expr ")"')
    def expr(self, p):
        return not p.expr

    @_("STRING")
    def expr(self, p):
        return p.STRING

    @_('JOIN "(" STRING "," expr_list ")"')
    def expr(self, p):
        # convert expression list to strings
        return p.STRING.join([str(x) for x in p.expr_list])

    @_('expr IN "(" expr_list ")"')
    def expr(self, p):
        return p.expr in p.expr_list

    @_("expr")
    def expr_list(self, p):
        return [p.expr]

    @_('expr_list "," expr')
    def expr_list(self, p):
        p.expr_list.append(p.expr)
        return p.expr_list

    @_(
        "expr EQ expr",
        "expr GT expr",
        "expr LT expr",
        "expr GE expr",
        "expr LE expr",
        "expr NE expr",
        "expr AND expr",
        "expr OR expr",
    )
    def expr(self, p):
        # Type checking: Ensure both expressions are of the same type
        if type(p.expr0) != type(p.expr1):
            raise TypeError(
                f"Type mismatch: {type(p.expr0).__name__} and {type(p.expr1).__name__}"
            )

        if p[1] == "=":
            return p.expr0 == p.expr1
        elif p[1] == ">":
            return p.expr0 > p.expr1
        elif p[1] == "<":
            return p.expr0 < p.expr1
        elif p[1] == ">=":
            return p.expr0 >= p.expr1
        elif p[1] == "<=":
            return p.expr0 <= p.expr1
        elif p[1] == "<>":
            return p.expr0 != p.expr1
        elif p[1] == "AND":
            return p.expr0 and p.expr1
        elif p[1] == "OR":
            return p.expr0 or p.expr1

    @_("NAME")
    def expr(self, p):
        value = self.env.get(p.NAME)
        if not isinstance(value, (int, float, bool, str)):
            value = self.parse(p.NAME)
        return value

    @_("NUMBER")
    def expr(self, p):
        return p.NUMBER

    @_("TRUE")
    def expr(self, p):
        return True

    @_("FALSE")
    def expr(self, p):
        return False
    
    @_('STR "(" expr ")"')
    def expr(self, p):
        if type(p.expr) == float:
            formatted = f"{p.expr:.3f}"
            if 0 < abs(p.expr) < 1:
                formatted = formatted.replace("0.", ".")
        else:
            formatted = str(p.expr)            
                
        return formatted
