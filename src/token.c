#include "token.h"

Token *new_tok(TokenType type, char *lit)
{
  Token *tok = malloc(sizeof(Token));
  tok->type = type;
  tok->lit = lit;
  return tok;
}
TokenStream *new_tok_stream()
{
  TokenStream *stream = calloc(1, sizeof(TokenStream));
  stream->tokens = calloc(START_TOK_SIZE, sizeof(Token));
  stream->count = 0;
  stream->pos = 0;
  stream->size = START_TOK_SIZE;
  return stream;
}

void tok_stream_push(TokenStream *stream, Token *tok)
{
  if (stream->count == stream->size)
  {
    stream->size *= 2;
    stream->tokens = realloc(stream->tokens, stream->size * sizeof(Token));
  }
  stream->tokens[stream->count++] = *tok;
}

Token *tok_stream_next(TokenStream *stream)
{
  if (stream->size >= stream->pos)
    return &stream->tokens[stream->pos++];
  return new_tok(TOK_EOF, "<Eof>");
}

Token *tok_stream_peek(TokenStream *stream)
{
  if (stream->size >= stream->pos)
    return &stream->tokens[stream->pos];
  return new_tok(TOK_EOF, "<Eof>");
}
