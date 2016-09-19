#include <stdio.h>
#include <assert.h>
#include "union_with_empty_builder.h"

#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(UnionWithEmpty, x)
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

static size_t create_works(uint8_t *buf)
{
  flatcc_builder_t builder;
  flatcc_builder_t *B = &builder;
  flatcc_builder_init(B);

  ns(Message_start_as_root(B));
  uint32_t to[] = {1,2,3};
  uint32_t from = 5;
  ns(Message_to_create(B, to, ARRAYSIZE(to)));
  ns(Message_from_add(B, from));

  ns(RequestSomething_ref_t) req = ns(RequestSomething_create(B));
  ns(Message_contents_add(B, ns(MessageContents_as_RequestSomething(req))));
  ns(Message_end_as_root(B));

  size_t size = flatcc_builder_get_buffer_size(B);
  flatcc_builder_copy_buffer(B, buf, size);

  flatcc_builder_clear(B);
  return size;
}

static size_t create_fails(uint8_t *buf)
{
  flatcc_builder_t builder;
  flatcc_builder_t *B = &builder;
  flatcc_builder_init(B);

  ns(RequestSomething_ref_t) req = ns(RequestSomething_create(B));

  ns(Message_start_as_root(B));
  uint32_t to[] = {1,2,3};
  uint32_t from = 5;
  ns(Message_to_create(B, to, ARRAYSIZE(to)));
  ns(Message_from_add(B, from));
  ns(Message_contents_add(B, ns(MessageContents_as_RequestSomething(req))));
  ns(Message_end_as_root(B));

  size_t size = flatcc_builder_get_buffer_size(B);
  flatcc_builder_copy_buffer(B, buf, size);  
  flatcc_builder_clear(B);
  return size;
}

static void decode(const uint8_t *buf)
{
  ns(Message_table_t) dec = ns(Message_as_root(buf));
  printf("type = '%s'\n", ns(MessageContents_type_name(ns(Message_contents_type(dec)))));
}

int main()
{
  uint8_t buf[1024];
  create_works(buf);
  create_fails(buf);
  decode(buf);
  return 0;
}
