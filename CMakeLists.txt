cmake_minimum_required(VERSION 3.2)
project(data_structure_c)

# set(CMAKE_C_COMPILER "/usr/bin/gcc-4.8")
#set(CMAKE_C_COMPILER "D:/ProgramFiles/cygwin64/bin/gcc.exe")
set(SOURCE_FILES
        src/lib/geometry_algorithm/geodist.h
        src/lib/geometry_algorithm/geodist.c
        src/lib/geometry_algorithm/geometry_algorithm.c
        src/lib/geometry_algorithm/geometry_algorithm.h
        src/lib/graph/graph_algorithm.c
        src/lib/graph/graph_algorithm.h
#        src/lib/encryption/rsa.c
#        src/lib/encryption/cbc_des.c
#        src/lib/encryption/cbc_des.h
#        src/lib/encryption/encrypt.h
#        src/lib/encryption/des.c
#        src/lib/comprass/compress.c
#        src/lib/comprass/compress.h
#        src/lib/comprass/bit_ctrl.c
#        src/lib/comprass/bit_ctrl.h
        src/lib/numerical_evaluation/numerical_evaluation.h
        src/lib/numerical_evaluation/numerical_evaluation.c
        src/lib/sort/sort.c
        src/lib/sort/sort.h
        src/lib/graph/graph_dfs.c
        src/lib/graph/graph_dfs.h
        src/lib/graph/graph_bfs.c
        src/lib/graph/graph_bfs.h
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
        src/lib/arr_tool/arrTool.c
        src/lib/arr_tool/arrTool.h

        src/test/course/course.c
        src/test/course/course.h
        src/test/student/student.c
        src/test/student/student.h
        src/test/set_cover_test/set_cover_test.c
        src/test/set_cover_test/set_cover_test.h
#		src/test/socket_transfer/socket_transfer.c
#		src/test/socket_transfer/socket_transfer.h

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
        src/test/graph_test/graph_test.c
        src/test/graph_test/graph_bfs_test.c
        src/test/graph_test/graph_dfs_test.c
        src/test/sort_test.c
#        src/test/compress_test/huff_compress_test.c
#        src/test/compress_test/lz77_compress_test.c
#        src/test/des_test/cbc_des_test.c
        src/test/graph_test/mini_tree_from_graph.c
        src/test/graph_test/shortest_tree_from_graph.c
        src/test/graph_test/travel_city_problem_test.c
        src/test/geometry_algorithm_test/line_intersect_test.c
        src/test/geometry_algorithm_test/cvxhull_test.c
        src/test/geometry_algorithm_test/arclen_test.c
        src/main/main.c
        src/main/student_manage/student_manage.h
        src/main/student_manage/student_manage.c

        src/test/test.h
        src/test/leetcode/test6/test6.c
        src/test/leetcode/test6/test6.h
        src/test/leetcode/test7/test7.c
        src/test/leetcode/test7/test7.h src/test/leetcode/test8/test8.h src/test/leetcode/test8/test8.c src/test/leetcode/test9/test9.c src/test/leetcode/test9/test9.h src/test/leetcode/test10/test10.c src/test/leetcode/test10/test10.h src/test/leetcode/test11/test11.c src/test/leetcode/test11/test11.h)

add_executable(data_structure_c ${SOURCE_FILES})
target_link_libraries(data_structure_c m)
