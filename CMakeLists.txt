cmake_minimum_required(VERSION 3.2)
project(data_structure_c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/lib/graph/graph.h
        src/lib/graph/graph.c
        src/lib/bitree/pqueue.h
        src/lib/bitree/heap.c
        src/lib/bitree/heap.h
        src/lib/bitree/bitree_avl.c
        src/lib/bitree/bitree_avl.h
        src/lib/bitree/bitree_traverse.c
        src/lib/bitree/bitree_traverse.h
        src/lib/bitree/bitree.c
        src/lib/bitree/bitree.h
        src/lib/cfg_op/cfg_op.c
        src/lib/cfg_op/cfg_op.h
        src/lib/des/des.c
        src/lib/des/des.h
        src/lib/hash_table_linked/linked_hash_table.c
        src/lib/hash_table_linked/linked_hash_table.h
        src/lib/hash_table_open_addressed/open_addr_hash_table.h
        src/lib/hash_table_open_addressed/open_addr_hash_table.c
        src/lib/list/list.h
        src/lib/list/list.c
        src/lib/list_double_cycle/dlist.c
        src/lib/list_double_cycle/dlist.h
        src/lib/list_single_cycle/clist.c
        src/lib/list_single_cycle/clist.h
        src/lib/mylog/mylog.c
        src/lib/mylog/mylog.h
        src/lib/queue/queue.h
        src/lib/queue/queue_my.c
        src/lib/set/set.c
        src/lib/set/set.h
        src/lib/set_cover/set_cover.c
        src/lib/set_cover/set_cover.h
        src/lib/stack/stack.h
        src/lib/stack/stack_my.c
        src/lib/str_tool/str_tool.c
        src/lib/str_tool/str_tool.h

        src/test/student/student.c
        src/test/student/student.h
        src/test/set_cover_test/set_cover_test.c
        src/test/set_cover_test/set_cover_test.h

        src/test/hash_table_linked_test.c
        src/test/hash_table_open_addressed_test.c
        src/test/queue_test.c
        src/test/set_test.c
        src/test/set_cover_test.c
        src/test/stack_test.c
        src/test/bitree_test.c
        src/test/bitree_avl_test.c
        src/test/heap_test.c
        src/test/parcels.c
        src/test/graph_test.c
        src/test/main.c
        src/test/test.h)
add_executable(data_structure_c ${SOURCE_FILES})