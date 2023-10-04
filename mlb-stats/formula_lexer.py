from sly import Lexer


class CalcLexer(Lexer):
    tokens = {
        NAME,
        NUMBER,
        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        GE,
        LE,
        NE,
        EQ,
        GT,
        LT,
        NOT,
        AND,
        OR,
        IN,
        TRUE,
        FALSE,
        IF,
        JOIN,
        STR,
        STRING,
    }

    ignore = " \t"

    # Tokens
    literals = {"(", ")", ","}
    
    PLUS    = r'\+'
    MINUS   = r'-'
    TIMES   = r'\*'
    DIVIDE  = r'/'

    GE = r">="
    LE = r"<="
    NE = r"<>"
    EQ = r"="
    GT = r">"
    LT = r"<"
    
    NAME = r"([a-zA-Z_][a-zA-Z0-9_]*|2B|3B)"
    NAME["TRUE"] = TRUE
    NAME["FALSE"] = FALSE
    NAME["IF"] = IF
    NAME["AND"] = AND
    NAME["OR"] = OR
    NAME["NOT"] = NOT
    NAME["IN"] = IN
    NAME["JOIN"] = JOIN
    NAME["STR"] = STR

    @_(r'\d+')
    def NUMBER(self, t):
        t.value = int(t.value)
        return t

    @_(r'"(\\.|[^"\\])*"', r"'(\\.|[^'\\])*'")
    def STRING(self, t):
        # Remove quotes
        t.value = t.value[1:-1].replace('\\"', '"').replace("\\'", "'")
        return t
