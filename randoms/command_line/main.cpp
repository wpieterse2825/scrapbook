#include <stdint.h>
#include <string.h>

#include <iostream>

namespace character {
    bool IsNumeric(char character);
    bool IsAlpha(char character);
    bool IsAlphaOrNumeric(char character);
} // namespace character

namespace string {
    bool Compare(const char* lhs, const char* rhs);
    bool Compare(const char* lhs, const char* rhs, size_t buffer_size);
} // namespace string

enum class ScannerTokenType : int64_t {
    EndOfFile = 0,
    CarriageReturn,
    NewLine,
    WhiteSpace,
    Tab,
    SingleQuote,
    DoubleQuote,
    Grave,
    OpenParenthesis,
    CloseParenthesis,
    OpenBrace,
    CloseBrace,
    OpenBracket,
    CloseBracket,
    OpenAngleBracket,
    CloseAngleBracket,
    Colon,
    Semicolon,
    Equal,
    Comma,
    ForwardSlash,
    BackwardSlash,
    Underscore,
    Dot,
    Plus,
    Minus,
    Asterisk,
    Tilde,
    Bang,
    Dollar,
    At,
    Hash,
    Percent,
    Circumflex,
    Ampersand,
    Pipe,
    QuestionMark,
    Alpha,
    Numeric,
    Unknown,
};

struct ScannerToken {
    ScannerTokenType type;

    char character;
};

namespace scanner_token {
    ScannerTokenType GetType(ScannerToken& token);
    char             GetCharacter(ScannerToken& token);

    bool IsEndOfFile(ScannerToken& token);
    bool IsCarriageReturn(ScannerToken& token);
    bool IsNewLine(ScannerToken& token);
    bool IsWhiteSpace(ScannerToken& token);
    bool IsTab(ScannerToken& token);
    bool IsSingleQuote(ScannerToken& token);
    bool IsDoubleQuote(ScannerToken& token);
    bool IsGrave(ScannerToken& token);
    bool IsOpenParenthesis(ScannerToken& token);
    bool IsCloseParenthesis(ScannerToken& token);
    bool IsOpenBrace(ScannerToken& token);
    bool IsCloseBrace(ScannerToken& token);
    bool IsOpenBracket(ScannerToken& token);
    bool IsCloseBracket(ScannerToken& token);
    bool IsOpenAngleBracket(ScannerToken& token);
    bool IsCloseAngleBracket(ScannerToken& token);
    bool IsColon(ScannerToken& token);
    bool IsSemicolon(ScannerToken& token);
    bool IsEqual(ScannerToken& token);
    bool IsComma(ScannerToken& token);
    bool IsForwardSlash(ScannerToken& token);
    bool IsBackwardSlash(ScannerToken& token);
    bool IsUnderscore(ScannerToken& token);
    bool IsDot(ScannerToken& token);
    bool IsPlus(ScannerToken& token);
    bool IsMinus(ScannerToken& token);
    bool IsAsterisk(ScannerToken& token);
    bool IsTilde(ScannerToken& token);
    bool IsBang(ScannerToken& token);
    bool IsDollar(ScannerToken& token);
    bool IsAt(ScannerToken& token);
    bool IsHash(ScannerToken& token);
    bool IsPercent(ScannerToken& token);
    bool IsCircumflex(ScannerToken& token);
    bool IsAmpersand(ScannerToken& token);
    bool IsPipe(ScannerToken& token);
    bool IsQuestionMark(ScannerToken& token);
    bool IsAlpha(ScannerToken& token);
    bool IsNumeric(ScannerToken& token);
    bool IsUnknown(ScannerToken& token);
} // namespace scanner_token

struct Scanner {
    const char* buffer;
    size_t      buffer_size;

    size_t current_index;
};

namespace scanner {
    Scanner Initialize(const char* buffer, size_t buffer_size);

    const char* GetBuffer(Scanner& scanner);
    size_t      GetBufferSize(Scanner& scanner);
    size_t      GetCurrentIndex(Scanner& scanner);

    ScannerToken ParseNextToken(Scanner& scanner);
    ScannerToken PeekNextToken(Scanner& scanner);

    namespace detail {
        bool IsAtEnd(Scanner& scanner);

        void ProcessToken(Scanner& scanner, ScannerToken& token, char current_character);

        char Advance(Scanner& scanner);
        char Peek(Scanner& scanner);
    } // namespace detail
} // namespace scanner

enum class ParserTokenType {
    Error     = -1,
    EndOfFile = 0,
    CarriageReturn,
    NewLine,
    WhiteSpace,
    Tab,
    LineComment,
    BlockComment,
    Identifier,
    String,
    Number,
    Unknown,
};

struct ParserToken {
    ParserTokenType type;

    size_t column;
    size_t row;

    const char* buffer;
    size_t      buffer_size;
};

namespace parser_token {
    ParserTokenType GetType(ParserToken& token) {
        return token.type;
    }

    size_t GetColumn(ParserToken& token) {
        return token.column;
    }

    size_t GetRow(ParserToken& token) {
        return token.row;
    }

    const char* GetBuffer(ParserToken& token) {
        return token.buffer;
    }

    size_t GetBufferSize(ParserToken& token) {
        return token.buffer_size;
    }

    bool IsError(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::Error;

        return is_type;
    }

    bool IsEndOfFile(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::EndOfFile;

        return is_type;
    }

    bool IsCarriageReturn(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::CarriageReturn;

        return is_type;
    }

    bool IsNewLine(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::NewLine;

        return is_type;
    }

    bool IsWhiteSpace(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::WhiteSpace;

        return is_type;
    }

    bool IsTab(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::Tab;

        return is_type;
    }

    bool IsLineComment(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::LineComment;

        return is_type;
    }

    bool IsBlockComment(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::BlockComment;

        return is_type;
    }

    bool IsIdentifier(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::Identifier;

        return is_type;
    }

    bool IsString(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::String;

        return is_type;
    }

    bool IsNumber(ParserToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ParserTokenType::Number;

        return is_type;
    }
} // namespace parser_token

struct Parser {
    Scanner* scanner;

    size_t current_column;
    size_t current_row;
};

namespace parser {
    Parser Initialize(Scanner* scanner) {
        auto parser = Parser {
          .scanner        = scanner,
          .current_column = 0,
          .current_row    = 0,
        };

        return parser;
    }

    Scanner* GetScanner(Parser& parser) {
        return parser.scanner;
    }

    size_t GetCurrentColumn(Parser& parser) {
        return parser.current_column;
    }

    size_t GetCurrentRow(Parser& parser) {
        return parser.current_row;
    }

    namespace detail {
        void ParseIdentifier(Parser& parser, ScannerToken& in_token, ScannerToken& peek_token, ParserToken& out_token) {
            auto parser_scanner = GetScanner(parser);
            auto start_index    = scanner::GetCurrentIndex(*parser_scanner) - 1;
            auto at_end         = false;

            while (true) {
                in_token = scanner::ParseNextToken(*parser_scanner);

                parser.current_column++;

                if (scanner_token::IsEndOfFile(in_token) == true) {
                    at_end = true;

                    out_token.type = ParserTokenType::Error;

                    break;
                } else if (scanner_token::IsUnknown(in_token) == true) {
                    at_end = true;

                    out_token.type = ParserTokenType::Error;

                    break;
                } else {
                    auto is_underscore = scanner_token::IsUnderscore(in_token);
                    auto is_alpha      = scanner_token::IsAlpha(in_token);
                    auto is_number     = scanner_token::IsNumeric(in_token);
                    auto is_valid      = is_underscore == true || is_alpha == true || is_number == true;

                    if (is_valid == false) {
                        break;
                    }
                }
            }

            if (at_end == false) {
                auto end_index = scanner::GetCurrentIndex(*parser_scanner);

                auto buffer = scanner::GetBuffer(*parser_scanner);

                out_token.type        = ParserTokenType::Identifier;
                out_token.buffer      = buffer + start_index;
                out_token.buffer_size = end_index - start_index;
            }
        }
    } // namespace detail

    ParserToken ParseNextToken(Parser& parser) {
        auto parser_scanner = GetScanner(parser);

        auto out_token  = ParserToken {};
        auto in_token   = scanner::ParseNextToken(*parser_scanner);
        auto peek_token = scanner::PeekNextToken(*parser_scanner);

        out_token.column = GetCurrentColumn(parser);
        out_token.row    = GetCurrentRow(parser);

        if (scanner_token::IsEndOfFile(in_token) == false) {
            parser.current_column++;
        }

        if (scanner_token::IsEndOfFile(in_token) == true) {
            out_token.type = ParserTokenType::EndOfFile;
        } else if (scanner_token::IsCarriageReturn(in_token) == true) {
            out_token.type = ParserTokenType::CarriageReturn;

            parser.current_column = 0;
        } else if (scanner_token::IsNewLine(in_token) == true) {
            out_token.type = ParserTokenType::NewLine;

            parser.current_row++;
            parser.current_column = 0;
        } else if (scanner_token::IsWhiteSpace(in_token) == true) {
            out_token.type = ParserTokenType::WhiteSpace;
        } else if (scanner_token::IsTab(in_token) == true) {
            out_token.type = ParserTokenType::Tab;
        } else if (scanner_token::IsForwardSlash(in_token) == true) {
            if (scanner_token::IsForwardSlash(peek_token) == true) {
                in_token = scanner::ParseNextToken(*parser_scanner);

                parser.current_column++;
            } else if (scanner_token::IsAsterisk(peek_token) == true) {
                in_token = scanner::ParseNextToken(*parser_scanner);

                parser.current_column++;
            } else {
                out_token.type = ParserTokenType::Error;
            }
        } else {
            auto is_single_quote = scanner_token::IsSingleQuote(in_token);
            auto is_double_quote = scanner_token::IsDoubleQuote(in_token);
            auto is_underscore   = scanner_token::IsUnderscore(in_token);
            auto is_alpha        = scanner_token::IsAlpha(in_token);

            auto is_string     = is_single_quote == true || is_double_quote == true;
            auto is_number     = scanner_token::IsNumeric(in_token);
            auto is_identifier = is_underscore == true || is_alpha == true;

            if (is_string == true) {
            } else if (is_number == true) {
            } else if (is_identifier == true) {
                detail::ParseIdentifier(parser, in_token, peek_token, out_token);
            } else {
                out_token.type = ParserTokenType::Unknown;
            }
        }

        return out_token;
    }
} // namespace parser

int main(int argument_count, const char** arguments) {
    auto message = "build 'hello/world/class 123 file.utx'";
    auto scanner = scanner::Initialize(message, strlen(message));
    auto parser  = parser::Initialize(&scanner);

    while (true) {
        auto token = parser::ParseNextToken(parser);

        if (parser_token::IsEndOfFile(token)) {
            break;
        } else if (parser_token::IsIdentifier(token)) {
            std::cout << "IDENTIFIER : ";

            for (auto index = size_t {0}; index < token.buffer_size; index++) {
                std::cout << token.buffer[index];
            }

            std::cout << std::endl;
        } else {
            std::cout << "UNKNOWN" << std::endl;
        }
    }

    return 0;
}

namespace character {
    bool IsNumeric(char character) {
        auto is_zero_or_above = character >= '0';
        auto is_nine_or_below = character <= '9';

        return is_zero_or_above && is_nine_or_below;
    }

    bool IsAlpha(char character) {
        auto is_a_or_above_lowercase = character >= 'a';
        auto is_z_or_below_lowercase = character <= 'z';
        auto is_a_to_z_lowercase     = is_a_or_above_lowercase && is_z_or_below_lowercase;

        auto is_a_or_above_uppercase = character >= 'A';
        auto is_z_or_below_uppercase = character <= 'Z';
        auto is_a_to_z_uppercase     = is_a_or_above_uppercase && is_z_or_below_uppercase;

        auto is_underscore = character == '_';

        return is_a_to_z_lowercase || is_a_to_z_uppercase || is_underscore;
    }

    bool IsAlphaOrNumeric(char character) {
        auto is_alpha   = IsAlpha(character);
        auto is_numeric = IsNumeric(character);

        return is_alpha || is_numeric;
    }
} // namespace character

namespace string {
    bool Compare(const char* lhs, const char* rhs) {
        auto difference = ::strcmp(lhs, rhs);

        return difference == 0;
    }

    bool Compare(const char* lhs, const char* rhs, size_t buffer_size) {
        auto difference = ::strncmp(lhs, rhs, buffer_size);

        return difference == 0;
    }
} // namespace string

namespace scanner_token {
    ScannerTokenType GetType(ScannerToken& token) {
        return token.type;
    }

    char GetCharacter(ScannerToken& token) {
        return token.character;
    }

    bool IsEndOfFile(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::EndOfFile;

        return is_type;
    }

    bool IsCarriageReturn(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::CarriageReturn;

        return is_type;
    }

    bool IsNewLine(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::NewLine;

        return is_type;
    }

    bool IsWhiteSpace(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::WhiteSpace;

        return is_type;
    }

    bool IsTab(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Tab;

        return is_type;
    }

    bool IsSingleQuote(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::SingleQuote;

        return is_type;
    }

    bool IsDoubleQuote(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::DoubleQuote;

        return is_type;
    }

    bool IsGrave(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Grave;

        return is_type;
    }

    bool IsOpenParanthesis(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::OpenParenthesis;

        return is_type;
    }

    bool IsCloseParanthesis(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::CloseParenthesis;

        return is_type;
    }

    bool IsOpenBrace(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::OpenBrace;

        return is_type;
    }

    bool IsCloseBrace(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::CloseBrace;

        return is_type;
    }

    bool IsOpenBracket(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::OpenBracket;

        return is_type;
    }

    bool IsCloseBracket(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::CloseBracket;

        return is_type;
    }

    bool IsOpenAngleBracket(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::OpenAngleBracket;

        return is_type;
    }

    bool IsCloseAngleBracket(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::CloseAngleBracket;

        return is_type;
    }

    bool IsColon(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Colon;

        return is_type;
    }

    bool IsSemicolon(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Semicolon;

        return is_type;
    }

    bool IsEqual(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Equal;

        return is_type;
    }

    bool IsComma(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Comma;

        return is_type;
    }

    bool IsForwardSlash(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::ForwardSlash;

        return is_type;
    }

    bool IsBackwardSlash(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::BackwardSlash;

        return is_type;
    }

    bool IsUnderscore(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Underscore;

        return is_type;
    }

    bool IsDot(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Dot;

        return is_type;
    }

    bool IsPlus(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Plus;

        return is_type;
    }

    bool IsMinus(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Minus;

        return is_type;
    }

    bool IsAsterisk(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Asterisk;

        return is_type;
    }

    bool IsTilde(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Tilde;

        return is_type;
    }

    bool IsBang(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Bang;

        return is_type;
    }

    bool IsDollar(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Dollar;

        return is_type;
    }

    bool IsAt(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::At;

        return is_type;
    }

    bool IsHash(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Hash;

        return is_type;
    }

    bool IsPercent(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Percent;

        return is_type;
    }

    bool IsCircumflex(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Circumflex;

        return is_type;
    }

    bool IsAmpersand(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Ampersand;

        return is_type;
    }

    bool IsPipe(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Pipe;

        return is_type;
    }

    bool IsQuestionMark(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::QuestionMark;

        return is_type;
    }

    bool IsAlpha(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Alpha;

        return is_type;
    }

    bool IsNumeric(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Numeric;

        return is_type;
    }

    bool IsUnknown(ScannerToken& token) {
        auto type    = GetType(token);
        auto is_type = type == ScannerTokenType::Unknown;

        return is_type;
    }
} // namespace scanner_token

namespace scanner {
    Scanner Initialize(const char* buffer, size_t buffer_size) {
        auto scanner = Scanner {
          .buffer        = buffer,
          .buffer_size   = buffer_size,
          .current_index = 0,
        };

        return scanner;
    }

    const char* GetBuffer(Scanner& scanner) {
        return scanner.buffer;
    }

    size_t GetBufferSize(Scanner& scanner) {
        return scanner.buffer_size;
    }

    size_t GetCurrentIndex(Scanner& scanner) {
        return scanner.current_index;
    }

    ScannerToken ParseNextToken(Scanner& scanner) {
        auto token             = ScannerToken {};
        auto current_character = detail::Advance(scanner);

        detail::ProcessToken(scanner, token, current_character);

        return token;
    }

    ScannerToken PeekNextToken(Scanner& scanner) {
        auto token             = ScannerToken {};
        auto current_character = detail::Peek(scanner);

        detail::ProcessToken(scanner, token, current_character);

        return token;
    }

    namespace detail {
        bool IsAtEnd(Scanner& scanner) {
            auto buffer_size          = GetBufferSize(scanner);
            auto current_index        = GetCurrentIndex(scanner);
            auto is_current_over_size = current_index >= buffer_size;

            return is_current_over_size;
        }

        void ProcessToken(Scanner& scanner, ScannerToken& token, char current_character) {
            token.character = current_character;

            switch (current_character) {
                case '\0':
                    token.type = ScannerTokenType::EndOfFile;
                    break;
                case '\r':
                    token.type = ScannerTokenType::CarriageReturn;
                    break;
                case '\n':
                    token.type = ScannerTokenType::NewLine;
                    break;
                case ' ':
                    token.type = ScannerTokenType::WhiteSpace;
                    break;
                case '\t':
                    token.type = ScannerTokenType::Tab;
                    break;
                case '\'':
                    token.type = ScannerTokenType::SingleQuote;
                    break;
                case '"':
                    token.type = ScannerTokenType::DoubleQuote;
                    break;
                case '`':
                    token.type = ScannerTokenType::Grave;
                    break;
                case '(':
                    token.type = ScannerTokenType::OpenParenthesis;
                    break;
                case ')':
                    token.type = ScannerTokenType::CloseParenthesis;
                    break;
                case '{':
                    token.type = ScannerTokenType::OpenBrace;
                    break;
                case '}':
                    token.type = ScannerTokenType::CloseBrace;
                    break;
                case '[':
                    token.type = ScannerTokenType::OpenBracket;
                    break;
                case ']':
                    token.type = ScannerTokenType::CloseBracket;
                    break;
                case '<':
                    token.type = ScannerTokenType::OpenAngleBracket;
                    break;
                case '>':
                    token.type = ScannerTokenType::CloseAngleBracket;
                    break;
                case ':':
                    token.type = ScannerTokenType::Colon;
                    break;
                case ';':
                    token.type = ScannerTokenType::Semicolon;
                    break;
                case '=':
                    token.type = ScannerTokenType::Equal;
                    break;
                case ',':
                    token.type = ScannerTokenType::Comma;
                    break;
                case '/':
                    token.type = ScannerTokenType::ForwardSlash;
                    break;
                case '\\':
                    token.type = ScannerTokenType::BackwardSlash;
                    break;
                case '_':
                    token.type = ScannerTokenType::Underscore;
                    break;
                case '.':
                    token.type = ScannerTokenType::Dot;
                    break;
                case '+':
                    token.type = ScannerTokenType::Plus;
                    break;
                case '-':
                    token.type = ScannerTokenType::Minus;
                    break;
                case '*':
                    token.type = ScannerTokenType::Asterisk;
                    break;
                case '~':
                    token.type = ScannerTokenType::Tilde;
                    break;
                case '!':
                    token.type = ScannerTokenType::Bang;
                    break;
                case '$':
                    token.type = ScannerTokenType::Dollar;
                    break;
                case '@':
                    token.type = ScannerTokenType::At;
                    break;
                case '#':
                    token.type = ScannerTokenType::Hash;
                    break;
                case '%':
                    token.type = ScannerTokenType::Percent;
                    break;
                case '^':
                    token.type = ScannerTokenType::Circumflex;
                    break;
                case '&':
                    token.type = ScannerTokenType::Ampersand;
                    break;
                case '|':
                    token.type = ScannerTokenType::Pipe;
                    break;
                case '?':
                    token.type = ScannerTokenType::QuestionMark;
                    break;
                default:
                    if (character::IsNumeric(current_character)) {
                        token.type = ScannerTokenType::Numeric;
                    } else if (character::IsAlpha(current_character)) {
                        token.type = ScannerTokenType::Alpha;
                    } else {
                        token.type = ScannerTokenType::Unknown;
                    }

                    break;
            }
        }

        char Advance(Scanner& scanner) {
            auto is_at_end = IsAtEnd(scanner);
            if (is_at_end == true) {
                return '\0';
            }

            auto buffer            = GetBuffer(scanner);
            auto current_index     = GetCurrentIndex(scanner);
            auto current_character = buffer[current_index];

            scanner.current_index++;

            return current_character;
        }

        char Peek(Scanner& scanner) {
            auto is_at_end = IsAtEnd(scanner);
            if (is_at_end == true) {
                return '\0';
            }

            auto buffer            = GetBuffer(scanner);
            auto current_index     = GetCurrentIndex(scanner);
            auto current_character = buffer[current_index];

            return current_character;
        }
    } // namespace detail
} // namespace scanner
