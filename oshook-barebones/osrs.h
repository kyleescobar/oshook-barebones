#pragma once
#include <stdint.h>
#include <vector>
namespace osrs
{
	namespace functions
	{
        typedef void* (*fn_fix_object_definition)(void* ptr);

        typedef void* (*fn_get_object_definition)(int object_id);

        typedef void* (*fn_fix_npc_definition)(void* p1, void* empty);

        typedef void* (*fn_get_item_definition)(void* p1, int id);

        typedef void (*fn_world_to_screen)(void* ptr, int floor, uint32_t pos_x, uint32_t pos_y, int pos_z);

        typedef void (*fn_print_chat)(int id, const char** name, const char** text);

        typedef void (*fn_render_scene)(void* param_1, uintptr_t param_2, uintptr_t param_3, uint32_t param_4,
            uint32_t param_5, uint32_t param_6, uint32_t param_7, uint32_t param_8);

        typedef void (*fn_do_action)(int pos_1, uint32_t pos_2, int action_id, int target_id, uintptr_t param_5, const char** param_6,
            uintptr_t param_7, uint32_t param_8, uintptr_t interface_ptr);

        typedef void* (*fn_get_varb_definition)(void*, int);

        typedef void* (*fn_projectiles)(void);
	}
}

namespace osrs
{

#pragma pack(push,4)
    struct vec2 {
        int x;
        int y;

        void operator=(const vec2& v1) {
            x = v1.x;
            y = v1.y;
        }

        vec2(const vec2& v1) {
            x = v1.x;
            y = v1.y;
        }

        vec2(int x, int y) : x(x), y(y) {}

        vec2() {
            x = 0;
            y = 0;
        }
    };

    struct vec3 {
        int x;
        int y;
        int z;

        vec3(int x, int y, int z) : x(x), y(y), z(z) {}

        vec3() {
            x = 0;
            y = 0;
            z = 0;
        }
    };

    struct osrs_ptr {
        void* ptr_meta;
        void* ptr_object;
    };

    class action {
    public:
        char* str_start; //0x0000
        char* str_end; //0x0008
        char* str_reserved; //0x0010
        char pad_0018[8]; //0x0018
    }; //Size: 0x0020
    class npc_definition {
    public:
        int32_t id; //0x0000
        char pad_0004[4]; //0x0004
        char* name; //0x0008
        char* name_end_ptr; //0x0010
        char* N000065E9; //0x0018
        char pad_0020[232]; //0x0020
        class action actions[5]; //0x0108
        int32_t visible_on_minimap; //0x01A8
        int32_t combat_lvl; //0x01AC
        char pad_01B0[40]; //0x01B0
        int32_t version; //0x01D8
        char pad_01DC[4]; //0x01DC
        int32_t* version_array; //0x01E0
        int32_t version_index; //0x01E8
        int32_t version_index_2; //0x01EC
        int32_t interactable; //0x01F0
        int32_t pet; //0x01F4
    }; //Size: 0x01F8

    class redbar {
    public:
        char pad_0000[40]; //0x0000
        int32_t max_width; //0x0028
        char pad_002C[428]; //0x002C
    }; //Size: 0x01D8

    class greenbar_ptr {
    public:
        char pad_0000[8]; //0x0000
        void* N0000026E; //0x0008
        char pad_0010[8]; //0x0010
        class greenbar* N00000270; //0x0018
        char pad_0020[64]; //0x0020
    }; //Size: 0x0060

    class greenbar {
    public:
        char pad_0000[8]; //0x0000
        int32_t green_width; //0x0008
        char pad_000C[68]; //0x000C
    }; //Size: 0x0050
    class hpbars {
    public:
        char pad_0000[8]; //0x0000
        class redbar* ptr1; //0x0008
        class greenbar_ptr_base* greenbar_base; //0x0018
        class greenbar_ptr* greenbar; //0x0018
    };

    class hpbar_pts {
    public:
        char pad_0000[0x10]; //0x0000
        void* p3;

        class hpbars* ptr_to_hpbars; //0x0018
    }; //Size: 0x00C0
    class player_composition {
    public:
        int32_t* equipment_ids; //0x0000
        int32_t* equipment_ids_end; //0x0008
        int32_t* equipment_ids_capacity; //0x0010
        char pad_0018[64]; //0x0018
        int32_t* body_colors; //0x0058
        int32_t* body_colors_end; //0x0060
        int32_t* body_colors_capacity; //0x0068
        char pad_0070[44]; //0x0070
        int32_t npc_id_transform; //0x009C
        uint64_t hash_1; //0x00A0
        uint64_t hash_2; //0x00A8
    }; //Size: 0x00B0
    class player_definition {
    public:
        char* name_nonascii;
        char pad_0000[24];
        char* name; //0x0020
    }; //Size: 0x028
    class npc {
    public:
        char pad_0000[8]; //0x0000
        int unk_check;
        char pad[4];
        int position_x; //0x0010
        int position_y; //0x0014
        int rotation; //0x0018
        char pad_001C[188]; //0x001C
        class hpbar_pts* HEALTHBAR; //0x00D8
        char pad_00E0[8]; //0x00E0
        int32_t target_index; //0x00E8
        char pad_00EC[92]; //0x00EC
        int z;
        char pad_00asd[516]; //0x001C
        npc_definition* def; //0x0350


        std::string name() {
            if (def)
                return std::string(def->name);
            else
                return "";
        }

        int x() {
            return position_x;
        }

        int y() {
            return position_y;
        }

        int tile_x() {
            return position_x >> 7;
        }

        int tile_y() {
            return position_y >> 7;
        }

        int target_id() {
            return target_index;
        }

        int height() {
            return z;
        }

        bool has_healthbar() {
            if (HEALTHBAR->p3)
                return true;
            else
                return false;
        }

        int health_ratio() {
            if (HEALTHBAR->ptr_to_hpbars && HEALTHBAR->ptr_to_hpbars->greenbar &&
                HEALTHBAR->ptr_to_hpbars->greenbar->N00000270) {
                int width = HEALTHBAR->ptr_to_hpbars->greenbar->N00000270->green_width;
                int max_width = HEALTHBAR->ptr_to_hpbars->ptr1->max_width;
                if (max_width)
                    return ((float)width / (float)max_width) * 100;
            }
            return 0;
        }
    }; //Size: 0x0358

    class varb_definition {
    public:
        int id;
        int bit1;
        int bit2;
        int unk;
    };

    class player {
    public:
        void* vtable;
        char pad_0000[8]; //0x0000
        int32_t position_x; //0x0010
        int32_t position_y; //0x0014
        int32_t rotation; //0x0018
        char pad_001C[188]; //0x001C
        class hpbar_pts* HEALTHBAR; //0x00D8
        char pad_00E0[8]; //0x00E0
        int32_t target_index; //0x00E8
        char pad_00EC[92]; //0x00EC
        int32_t z; //0x0148
        char pad_014C[516]; //0x014C
        player_definition* def; //0x0350
        player_composition* comp;
        char pad_0358[112]; //0x0358
        int32_t combat_lvl; //0x03D0

        player_definition* definition() {
            return def;
        }

        std::string name() {
            if (def)
                return std::string(def->name);
            else
                return "";
        }

        int x() {
            return position_x;
        }

        int y() {
            return position_y;
        }

        int tile_x() {
            return position_x >> 7;
        }

        int tile_y() {
            return position_y >> 7;
        }

        int target_id() {
            return target_index;
        }

        int height() {
            return z;
        }

        bool has_healthbar() {
            if (HEALTHBAR->p3)
                return true;
            else
                return false;
        }

        int health_ratio() {
            if (HEALTHBAR->ptr_to_hpbars && HEALTHBAR->ptr_to_hpbars->greenbar &&
                HEALTHBAR->ptr_to_hpbars->greenbar->N00000270) {
                int width = HEALTHBAR->ptr_to_hpbars->greenbar->N00000270->green_width;
                int max_width = HEALTHBAR->ptr_to_hpbars->ptr1->max_width;
                if (max_width)
                    return ((float)width / (float)max_width) * 100;
            }
            return 0;
        }

        int combat_level() {
            return combat_lvl;
        }
    }; //Size: 0x03D4

    class object_definition {
    public:
        int32_t object_id; //0x0000
        char pad_0004[52]; //0x0004
        char* object_name; //0x0038
        char pad_0040[120]; //0x0040
        int32_t x; //0x00B8
        int32_t y; //0x00BC
        int32_t z; //0x00C0
        int shadow;
        int blocking;
        char pad_00C4[68]; //0x00C4
        class action actions[5]; //0x0110
        char pad_01B0[56]; //0x01B0
        int32_t version;
        char pad[4];
        void* version_array; //0x01F0
        int32_t version_index; //0x01F8
        int32_t version_index_2; //0x01FC
    }; //Size: 0x0200
    class jagex_str {
    public:
        char* str; //0x0000
        char* str_end; //0x0008
        char* str_reserved; //0x0010
        char* unk; //0x0018
    }; //Size: 0x0020

    class item_definition {
    public:
        int32_t item_id; //0x0000
        int32_t N00000237; //0x0004
        const char* name; //0x0008
        char pad_0010[188]; //0x0010
        int32_t cost; //0x00CC
        char pad_00D0[48]; //0x00D0
        class jagex_str ground_actions[5]; //0x0100
        char pad_01A0[40]; //0x01A0
        class jagex_str inv_actions[5]; //0x01C8
        char pad_0268[144]; //0x0268
        void* N0000014F; //0x02F8

        std::string get_name() {
            return std::string(name);
        }

        int get_cost() {
            return cost;
        }
    }; //Size: 0x0300

    class ground_item {
    public:
        char pad_0000[16]; //0x0000
        int32_t item_id; //0x0010
        int32_t item_count; //0x0014
        char pad_0018[24]; //0x0018

    }; //Size: 0x0030
    class linked_list {
    public:
        linked_list* last; //0x0000
        linked_list* next; //0x0008
        void* obj_meta; //0x0010
        class ground_item* object; //0x0018
    }; //Size: 0x0020
    class linked_list_first {
    public:
        class linked_list* end_of_list; //0x0000
        class linked_list* start_of_list; //0x0008
        char pad_0010[8]; //0x0010
    }; //Size: 0x0018
    class mouseover_entry {
    public:
        int32_t x; //0x0000
        int32_t y; //0x0004
        int32_t action_id; //0x0008
        int32_t short_id; //0x000C
        char pad_0010[8]; //0x0010
        char* action_name; //0x0018
        char pad_0020[24]; //0x0020
        char* target_name; //0x0038
        char pad_0040[32]; //0x0040
        uint64_t long_id; //0x0060
        char pad_0068[32]; //0x0068
    }; //Size: 0x0088

    class mouseover {
    public:
        char pad_0000[672]; //0x0000
        uint64_t action_count; //0x02B0
        class mouseover_entry mouseover_entries[500]; //0x0340
    }; //Size: 0x206E0
    class N00002E1A {
    public:
        char pad_0000[8]; //0x0000
    }; //Size: 0x0008
    class placeholder {
    public:
        void* vtable;
    };

    class renderable_object {
    public:
        char pad_0000[8]; //0x0000
        int32_t fine_x; //0x0008
        int32_t fine_y; //0x000C
        int32_t x; //0x0010
        int32_t y; //0x0014
        char pad_0018[16]; //0x0018
        placeholder* object; //0x0028
        char pad_0030[24]; //0x0030
        int64_t timer; //0x0048
        int64_t long_id; //0x0050
        int32_t unk_int; //0x0058
        int64_t object_highlight; //0x005C

    }; //Size: 0x0080
    class renderable_ptr {
    public:
        void* ptr_meta; //0x0000
        class renderable_object* renderable; //0x0008
    }; //Size: 0x0010
    class scene_tile {
    public:
        char pad_0000[36]; //0x0000
        int32_t x; //0x0024
        int32_t y; //0x0028
        char pad_002C[44]; //0x002C
        class attached_object* attached; //0x0058
        char pad_0060[56]; //0x0060
        int32_t renderable_count; //0x0098
        char pad_009C[4]; //0x009C
        void* renderables_start; //0x00A0
        void* renderables_end; //0x00A8
        char pad_00B0[24]; //0x00B0
        class renderable_ptr renderables[5]; //0x00C8
        char pad_0118[680]; //0x0118
        void* N00002DC0; //0x03C0
    }; //Size: 0x03C8

    class attached_object {
    public:
        int32_t height; //0x0000
        int32_t position_x; //0x0004
        int32_t position_y; //0x0008
        int32_t blocking; //0x000C
        int32_t blocking_secondary; //0x0010
        int32_t unk; //0x0014
        void* N0000115F; //0x0018
        void* object; //0x0020
        int32_t unk2; //0x0028
        int32_t unk3; //0x002C
        int32_t unk4; //0x0030
        int32_t unk5; //0x0034
        uint64_t long_id; //0x0038
        uint64_t object_highlight; //0x0040
    };

    class tile_ptr {
    public:
        void* ptr_meta; //0x0000
        class scene_tile* tile; //0x0008
    }; //Size: 0x0010
	
    class scene {
    public:
        char pad_0000[21800]; //0x0000
        int32_t floors; //0x5528
        int32_t scene_x; //0x552C
        int32_t scene_y; //0x5530
        int32_t N00002CD9; //0x5534
        int32_t N00002B74; //0x5538
        int32_t N00002CDB; //0x553C
        int32_t array_size; //0x5540
        int32_t N00002CDD; //0x5544
        tile_ptr* tile_array; //0x5548
        char pad_5550[2744]; //0x5550

    }; //Size: 0x6008

    class item_container {
    public:
        char pad_0000[8]; //0x0000
        int32_t* item_ids; //0x0008
        int32_t* item_ids_end; //0x0010
        void* item_ids_capacity; //0x0018
        char pad_0020[8]; //0x0020
        int32_t* item_counts; //0x0028
        int32_t* item_counts_end; //0x0030
        void* item_counts_capacity; //0x0038
        char pad_0040[264]; //0x0040

        size_t size() {
            return ((size_t)item_ids_end - (size_t)item_ids) / sizeof(int32_t);
        }

        int32_t find_first(int32_t id) {
            for (int i = 0; i < this->size(); i++) {
                if (item_ids[i] == id)
                    return i;
            }
            return -1;
        }
    }; //Size: 0x0148

    class item_containers {
    public:
        class item_container** containers; //0x0000
        int32_t container_count; //0x0008
    }; //Size: 0x010
#pragma pack(pop)
    enum actions {
        ACTION_OBJECT_INTERACT = 3,
        ACTION_BANK = 4,
        ACTION_INTERACT = 9,
        ACTION_FISH = 9,
        ACTION_ATTACK = 10,
        ACTION_FISH2 = 11,
        ACTION_INTERACT2 = 11,
        ACTION_INTERACT3 = 12,
        ACTION_INTERACT4 = 13,
        ACTION_TAKE = 20,
        ACTION_WALK = 23,
        ACTION_INVENTORY_USE_DEST = 31,
        ACTION_INVENTORY_PRIMARY = 33,
        ACTION_INVENTORY_DROP = 37,
        ACTION_INVENTORY_USE = 38,
        ACTION_INTERFACE_INTERACT = 57,
        ACTION_EXAMINE_OBJECT = 1002,
        ACTION_EXAMINE_NPC = 1003,
        ACTION_EXAMINE_GROUND_ITEM = 1004,
        ACTION_EXAMINE_INV_ITEM = 1005,
        ACTION_TRADE = 2047
    };
    enum interfaces {
        INTERFACE_BANK_EXIT = 786434,
        INTERFACE_BANK_ITEMCONTAINER = 786444,
        INTERFACE_BANK_WITHDRAW_ITEM = 786453,
        INTERFACE_BANK_WITHDRAW_NOTE = 786455,
        INTERFACE_BANK_QUANTITY_1 = 786459,
        INTERFACE_BANK_QUANTITY_5 = 786461,
        INTERFACE_BANK_QUANTITY_10 = 786463,
        INTERFACE_BANK_QUANTITY_X = 786465,
        INTERFACE_BANK_QUANTITY_ALL = 786467,
        INTERFACE_BANK_INVENTORY_ALL = 786473,
        INTERFACE_BANK_GEAR_ALL = 786475,
        INTERFACE_INVENTORY = 9764864,
        INTERFACE_QUICK_PRAYER = 10485775,
        INTERFACE_LOBBY_BUTTON = 24772686,

        INTERFACE_TAB_COMBAT_RM = 10747962,
        INTERFACE_TAB_SKILLS_RM = 10747963,
        INTERFACE_TAB_QUESTS_RM = 10747964,
        INTERFACE_TAB_INVENTORY_RM = 10747965,
        INTERFACE_TAB_GEAR_RM = 10747966,
        INTERFACE_TAB_PRAYER_RM = 10747967,
        INTERFACE_TAB_MAGIC_RM = 10747968,
        INTERFACE_TAB_FRIENDS_RM = 10747949,
        INTERFACE_TAB_ACCOUNT_RM = 10747948,
        INTERFACE_TAB_CLAN_RM = 10747947,
        INTERFACE_TAB_SETTINGS_RM = 10747950,
        INTERFACE_TAB_EMOTES_RM = 10747951,
        INTERFACE_TAB_MUSIC_RM = 10747952,

        INTERFACE_GEAR_HEAD = 25362447,
        INTERFACE_GEAR_CAPE = 25362448,
        INTERFACE_GEAR_NECK = 25362449,
        INTERFACE_GEAR_MAINHAND = 25362450,
        INTERFACE_GEAR_CHEST = 25362451,
        INTERFACE_GEAR_OFFHAND = 25362452,
        INTERFACE_GEAR_LEGS = 25362453,
        INTERFACE_GEAR_GLOVES = 25362454,
        INTERFACE_GEAR_BOOTS = 25362455,
        INTERFACE_GEAR_RING = 25362456,
        INTERFACE_GEAR_ARROWS = 25362457
    };
    enum containers {
        CONTAINER_INVENTORY = 19,
        CONTAINER_GEAR = 20,
        CONTAINER_BANK = 21
    };

    // Created with ReClass.NET 1.2 by KN4CK3R

    class component_ptr {
    public:
        void* meta_ptr; //0x0000
        void* component; //0x0008
    }; //Size: 0x0010

    class element_subclass {
    public:
        char pad_0000[1384]; //0x0000
        int32_t component_count; //0x0568
        char pad_056C[4]; //0x056C
        class component_ptr* components; //0x0570
        char pad_0578[144]; //0x0578
    }; //Size: 0x0608

    class element {
    public:
        char pad_0000[4]; //0x0000
        int32_t id; //0x0004
        char pad_0008[4]; //0x0008
        int32_t type; //0x000C
        char pad_0010[4]; //0x0010
        int32_t clientcode; //0x0014
        char pad_0018[4]; //0x0018
        int32_t x_mode; //0x001C
        int32_t y_mode; //0x0020
        char pad_0024[8]; //0x0024
        int32_t unk_x; //0x002C
        int32_t unk_y; //0x0030
        int32_t unk_width; //0x0034
        int32_t unk_height; //0x0038
        int32_t rel_x; //0x003C
        int32_t rel_y; //0x0040
        int32_t width; //0x0044
        int32_t height; //0x0048
        char pad_004C[8]; //0x004C
        int32_t parent_id; //0x0054
        int32_t hidden; //0x0058
        char pad_005C[172]; //0x005C
        char* element_str; //0x0108
        char pad_0110[184]; //0x0110
        class element_subclass* sub; //0x01C8
        char pad_01D0[1496]; //0x01D0
        void* N0000020D; //0x07A8

        void* get_component(int idx) {
            if (sub)
                if (idx < sub->component_count)
                    return sub->components[idx].component;
            return nullptr;
        }

        uintptr_t get_component_address(int idx) {
            if (sub)
                if (idx < sub->component_count)
                    return (uintptr_t)&sub->components[idx].meta_ptr;
            return 0;
        }
    };

    class interface_element_ptr {
    public:
        void* meta_ptr; //0x0000
        class element* element_ptr; //0x0008
    }; //Size: 0x0010

    class iface {
    public:
        char pad_0000[8]; //0x0000
        int32_t element_count; //0x0008
        char pad_000C[4]; //0x000C
        class interface_element_ptr* elements; //0x0010
    }; //Size: 0x0018
    class interface_list {
    public:
        class iface* interfaces; //0x0000
        char pad_0008[8]; //0x0008
        int32_t interface_count; //0x0010

        element* get_interface(int id) {
            int sub_id = id & 0x0000FFFF;
            int main_id = id >> 16;

            if (interfaces[main_id].element_count)
                return interfaces[main_id].elements[sub_id].element_ptr;
            return nullptr;
        }

        uintptr_t get_interface_address(int id) {
            int sub_id = id & 0x0000FFFF;
            int main_id = id >> 16;

            if (interfaces[main_id].element_count)
                return (uintptr_t)&interfaces[main_id].elements[sub_id].meta_ptr;
            return 0;
        }
    }; //Size: 0x0040

}
#pragma once


