#include <string>
#include <map>

using std::string;
using std::map;

enum TagType {

    JOURNAL_FILE,
    TEMP_FOLDER,
    SCHEMA,
    PRIMARY_KEY,
    
    END_OF_VOID_TAGS,
    
    /* base_core.dtd */

    BASE,
    TABLE,
    RELATION,
    INDEX,
    BASE_EXTRA,
    EDITOR_BASE_INFO,
    COLOR,
    FIELD,
    TABLE_EXTRA,
    COMMENT,
    EDITOR_TABLE_INFO,
    INDEX_REF,
    FIELD_EXTRA,
    QT_SPATIAL_SETTINGS,
    TIP,
    EDITOR_FIELD_INFO,
    FIELD_REF,
    RELATED_FIELD,
    RELATION_EXTRA,
    EDITOR_RELATION_INFO,
    COORDINATES,

    CUSTOM,
};


static const map<string, TagType> get_tag_map() {
  map<string, TagType> result;
#define TAG(name) result[#name] = name

    /* base_core.dtd */
    
    TAG(BASE);
    TAG(SCHEMA);
    TAG(TABLE);
    TAG(RELATION);
    TAG(INDEX);
    TAG(BASE_EXTRA);
    TAG(TEMP_FOLDER);
    TAG(JOURNAL_FILE);
    TAG(EDITOR_BASE_INFO);
    TAG(COLOR);
    TAG(FIELD);
    TAG(PRIMARY_KEY);
    TAG(TABLE_EXTRA);
    TAG(COMMENT);
    TAG(EDITOR_TABLE_INFO);
    TAG(INDEX_REF);
    TAG(FIELD_EXTRA);
    TAG(QT_SPATIAL_SETTINGS);
    TAG(TIP);
    TAG(EDITOR_FIELD_INFO);
    TAG(FIELD_REF);
    TAG(RELATED_FIELD);
    TAG(RELATION_EXTRA);
    TAG(EDITOR_RELATION_INFO);
    TAG(COORDINATES);
    
#undef TAG
        
  return result;
}

static const map<string, TagType> TAG_TYPES_BY_TAG_NAME = get_tag_map();

struct Tag {
  TagType type;
  string custom_tag_name;

  // This default constructor is used in the case where there is not enough space
  // in the serialization buffer to store all of the tags. In that case, tags
  // that cannot be serialized will be treated as having an unknown type. These
  // tags will be closed via implicit end tags regardless of the next closing
  // tag is encountered.
  Tag() : type(END_OF_VOID_TAGS) {}

  Tag(TagType type, const string &name) : type(type), custom_tag_name(name) {}

  bool operator==(const Tag &other) const {
    if (type != other.type) return false;
    if (type == CUSTOM && custom_tag_name != other.custom_tag_name) return false;
    return true;
  }

  inline bool is_void() const {
    return type < END_OF_VOID_TAGS;
  }

  inline bool can_contain(const Tag &tag) {
    TagType child = tag.type;

      switch (type) {
              
          default:
              return true;
      }
  }

  static inline Tag for_name(const string &name) {
    map<string, TagType>::const_iterator type = TAG_TYPES_BY_TAG_NAME.find(name);
    if (type != TAG_TYPES_BY_TAG_NAME.end()) {
      return Tag(type->second, string());
    } else {
      return Tag(CUSTOM, name);
    }
  }
};
