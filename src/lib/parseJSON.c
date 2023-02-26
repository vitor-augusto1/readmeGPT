#include "../includes/parseJSON.h"


const char* extract_the_text_from_api_response_json(char *text_to_parse)
{
  json_object *root = json_tokener_parse(text_to_parse);
  json_object *choices;
  const char *extracted_text;
  if (json_object_object_get_ex(root, "choices", &choices)) {
    struct json_object *choice = json_object_array_get_idx(choices, 0);
    struct json_object *text;
    json_object_object_get_ex(choice, "text", &text);
    extracted_text = json_object_get_string(text);
    json_object_put(root);
    return extracted_text;
  }
  return NULL;
}
