//
// Created by wangxn on 2016/4/20.
//


#include "graph_algorithm.h"
#include "../set/set.h"



/***************************************************************************************/
/**
 * 最小生成树的结构体的内存分配以及数据初始化
 */
MstVertex *mst_vertex_get_init(void *data,
                               double weight,
                               int (*match)(const void *key1, const void *key2),
                               void (*destroy)(void *data)) {
    MstVertex * retval = (MstVertex *)malloc(sizeof(MstVertex));
    if (retval == NULL) {
        printf("%s\n", "bfs_vertex_get_init() function fail, call malloc() fail");
        return NULL;
    }
    retval->data = data;
    retval->color = white;
    retval->weight = weight;
    retval->key = DBL_MAX;

    retval->match = match;
    retval->destroy = destroy;

    return retval;
}

/**
 * 最小生成树的结构体的匹配方法
 */
int mst_vertex_match(MstVertex *m1, MstVertex *m2) {
    if (m1->match != NULL) {
        return m1->match(m1->data, m2->data);
    } else {
        return -1;
    }
}

/**
 * 最小生成树的结构体的销毁函数
 */
void mst_vertex_destroy(MstVertex *mstVertex) {
    if (mstVertex == NULL) {
        return;
    }

    if (mstVertex->destroy != NULL) {
        mstVertex->destroy(mstVertex->data);
    }

    free(mstVertex);
}

/***************************************************************************************/

/**
 * 获取最短路径树需要的结构体
 */
PathVertex *path_vertex_get_init(void *data,
                                 double weight,
                                 int (*match)(const void *key1, const void *key2),
                                 void (*destroy)(void *data)) {
    PathVertex * retval = (PathVertex *)malloc(sizeof(PathVertex));
    if (retval == NULL) {
        printf("%s\n", "bfs_vertex_get_init() function fail, call malloc() fail");
        return NULL;
    }
    retval->data = data;
    retval->color = white;
    retval->weight = weight;
    retval->d = DBL_MAX;

    retval->match = match;
    retval->destroy = destroy;

    return retval;
}

/**
 * 最短路径树需要的结构体的匹配函数
 */
int path_vertex_match(PathVertex *pv1, PathVertex *pv2){
    if (pv1->match != NULL) {
        return pv1->match(pv1->data, pv2->data);
    } else {
        return -1;
    }
}

/**
 * 最短路径树需要的结构体的销毁函数
 */
void path_vertex_destroy(PathVertex *pv){
    if (pv == NULL) {
        return;
    }

    if (pv->destroy != NULL) {
        pv->destroy(pv->data);
    }

    free(pv);
}

/***************************************************************************************/

/**
 * 旅行商问题的结构体TspVertex的构造方法
 */
TspVertex *travel_city_problem_vertex_get_init(void *data,
                                 double x,
                                 double y,
                                 int (*match)(const void *key1, const void *key2),
                                 void (*destroy)(void *data)) {
    TspVertex * retval = (TspVertex *)malloc(sizeof(TspVertex));
    if (retval == NULL) {
        printf("%s\n", "bfs_vertex_get_init() function fail, call malloc() fail");
        return NULL;
    }
    retval->data = data;
    retval->color = white;
    retval->x = x;
    retval->y = y;

    retval->match = match;
    retval->destroy = destroy;

    return retval;
}

/**
 * 旅行商问题的结构体TspVertex的匹配函数
 */
int travel_city_problem_vertex_match(TspVertex *tv1, TspVertex *tv2){
    if (tv1->match != NULL) {
        return tv1->match(tv1->data, tv2->data);
    } else {
        return -1;
    }
}

/**
 *旅行商问题的结构体TspVertex的销毁函数
 */
void travel_city_problem_vertex_destroy(TspVertex *tv){
    if (tv == NULL) {
        return;
    }
    if (tv->destroy != NULL) {
        tv->destroy(tv->data);
    }
    free(tv);
}

/***************************************************************************************/





/**
 * 最小生成树
 *
 * 给定一个无方向的带权图G=(V,E)
 * 最小生成树为集合T,
 * T是以最小代价连接V中所有顶点所用边E的最小集合.
 * 集合T中的边能形成一棵树,这是因为每个顶点(除了第一个顶点,即根节点)都能向上找到它的一个父结点
 *
 * 从一个图中提取一棵树,这棵树包含所有的顶点,但是有最少的边
 *
 * Prim算法
 *
 *      每次选择一个与当前顶点最近的一个顶点,并将两个顶点之间的边加入到树中.
 *      贪心算法,但是可以提供不止于较优而是最优的结果
 *      不断的选择顶点,并计算边的权值,同时判断是否还有更有效的连接方式.类似于广度优先搜索,需要维护每个顶点的色值和键值
 *
 *      在图中所有的白色顶点中,选择键值最小的顶点u作为起始顶点,并标记其为黑色
 *      遍历与起始顶点的所有顶点v,设置v的键值为边(u,v)的权值,同时将u设置为v的父结点,并设置为黑色
 *
 *
 * 为一个无方向的带权图graph计算最小生成树.
 * 最小生成树从顶点start开始计算
 * 此操作会改变graph,
 * graph中的每个顶点必须包含MstVertex类型的数据.
 * 通过设置MstVertex.weight来指定每个边的权值
 * weight的值由传入graph_ins_edge的参数data2决定
 * M身体Vertex.data保存与顶点相关的数据,例如顶点标识符
 * graph.match用来比较MstVertex.data成员
 *
 * 一旦计算完成,最小生成树的相关数据将会返回到span,
 * span是存储MstVertex结构体的列表.
 * 在span中,父结点为NULL的顶点为最小生成树的根节点.
 * 其他每个顶点的parent成员都指向span中位于该顶点之前的那个顶点.
 * 访问span中的顶点,graph中的内存空间必须有效.
 *
 */
int mst(Graph *graph/*in*/,
        const MstVertex *start/*in*/,
        List *span/*out*/,
        int (*match)(const void *key1, const void *key2)/*in*/) {

    MstVertex *mst_vertex, *mst_temp, *adj_vertex;
    AdjList * adjList, *data;
    double minimum;
    int found, i;

    list_resetIterator(&(graph->adjlists));
    //遍历图中的所有顶点的列表,取出每个顶点
    while (list_hasNext(&(graph->adjlists))) {
        list_moveToNext(&(graph->adjlists));
        list_iterator(&(graph->adjlists), (void **)&data);
        mst_vertex = (MstVertex *)(data->vertex);

        //比较当前顶点和传参的start顶点
        if (match(mst_vertex, start)) {
        //相同,设置为起始顶点,设置颜色,键值,父结点,以及found(表示找到了起始节点)
            mst_vertex->color = white;
            mst_vertex->key = 0;      //起始节点不同于其他节点的地方,key为0
            mst_vertex->parent = NULL;
            found = 1;
        } else {
        //不相同,设置颜色,键值,父结点
            mst_vertex->color = white;
            mst_vertex->key = DBL_MAX;
            mst_vertex->parent = NULL;
        }
    }

    //判断found参数是否为1,否则退出函数
    if (!found) {
        return -1;
    }

    i = 0;
    while (i < graph_vcount(graph)) {
        minimum = DBL_MAX;

        //循环遍历图中的所有顶点,
        list_resetIterator(&graph_adjlists(graph));
        while (list_hasNext(&graph_adjlists(graph))) {
            list_moveToNext(&graph_adjlists(graph));
            list_iterator(&graph_adjlists(graph), (void **)(&data));
            mst_temp = (MstVertex *)(data->vertex);

            //找到颜色为白色, 键值最小的顶点以及其键值
            //初始时,只有起始节点的key为0,其他的节点的key都是DBL_MAX,所以找到的也就是起始节点
            if (mst_temp->color == white && mst_temp->key < minimum) {
                minimum = mst_temp->key;
                mst_vertex = mst_temp;
                adjList = data;
            }
        }

        //将这个顶点的颜色置为黑色
        mst_vertex->color = black;

        //遍历这个顶点的所有相邻顶点
        list_resetIterator(&(adjList->adjacent));
        while (list_hasNext(&(adjList->adjacent))) {
            list_moveToNext(&(adjList->adjacent));
            list_iterator(&(adjList->adjacent), (void **)(&adj_vertex));

            //并遍历图的所有顶点的列表,找到相邻顶点在图中顶点列表中的结构体
            list_resetIterator(&graph_adjlists(graph));
            while (list_hasNext(&graph_adjlists(graph))) {
                list_moveToNext(&graph_adjlists(graph));
                list_iterator(&graph_adjlists(graph), (void **)(&data));
                mst_temp = (MstVertex *)(data->vertex);
                //如果找到了
                if (match(mst_temp, adj_vertex)) {
                    //在这个顶点的颜色为白色,并且其weight值小于key值的情况下
                    //key值最小的是起始节点为0, 其他的节点的key都是DBL_MAX, 这是初始情况
                    if (mst_temp->color == white && adj_vertex->weight < mst_temp->key) {
                        // 设置key值为weight值
                        mst_temp->key = adj_vertex->weight;
                        //设置parent为当前while循环找到的顶点,
                        mst_temp->parent = mst_vertex;
                    }
                    //并且退出循环
                    break;
                }
            }
        }
        i++;
    }

    //初始化span的list集合
    list_init(span, NULL);
    //遍历图的所有节点
    list_resetIterator(&(graph_adjlists(graph)));
    while (list_hasNext(&(graph_adjlists(graph)))) {
        list_moveToNext(&(graph_adjlists(graph)));
        list_iterator(&(graph_adjlists(graph)), (void **) (&data));
        mst_temp = (MstVertex *)data->vertex;
        if (mst_temp->color == black) {
            //将图中的所有颜色为黑色的顶点加入到span中的尾部
            if (list_ins_next(span, list_tail(span), mst_temp) != 0) {
                list_destroy(span);
                return -1;
            }
        }
    }

    return 0;
}


/***************************************************************************************/

/**
 * 释放从顶点u到顶点v的边
 *
 * 理解:
 * 如果v点的最短路径估值 比  u点的最短路径估值加上weight的值 大
 * 那么将 u点的最短路径估值加上weight的值 复制给v点的最短路径估值
 * 同时, u最为v的父结点
 */
static  void relax(PathVertex *u, PathVertex *v, double weight) {

    if ( v->d > (u->d + weight)) {
        v->d = (u->d + weight);
        v->parent = u;
    }
    return;
}



/**
 * 最短路径
 *
 *  计算最短路径成功,返回0,否则,返回-1
 *
 *  会改变graph
 *
 *  graph的每个顶点必须包含PathVertex类型的数据
 *
 *  设置PathVertex.weight 的值来指定每个边的权值.
 *  weight的值由传入graph_ins_edge的参数data2来决定.
 *
 *  PathVertex.data来保存与顶点相关的数据
 *
 *  计算完成, 最短路径的相关信息将会返回给paths,paths存储PathVertex结构体的列表.
 *  在paths中, 起始顶点的父结点设置为NULL
 *  paths的顶点指向graph中实际的顶点,访问paths必须保证graph的内存空间有效.
 *
 *
 */
int shortest(Graph *graph/*in,out*/,
             const PathVertex *start/*in*/,
             List *paths/*out*/,
             int (*match)(const void *key1, const void *key2 )/*in*/) {

    AdjList *adjList, *adjList_temp;
    PathVertex *pth_vertex, *pth_vertex_tmp, *adj_vertex;
    double minimum;
    int found, i;

    found = 0;
    //遍历整个graph的所有节点,比对start是否存在于graph中,
    list_resetIterator(&graph_adjlists(graph));
    while (list_hasNext(&graph_adjlists(graph))) {
        list_moveToNext(&graph_adjlists(graph));
        list_iterator(&graph_adjlists(graph), (void **)&adjList_temp);
        pth_vertex_tmp = (PathVertex *)adjList_temp->vertex;
        //如果存在,对graph中的顶点初始化,
        //颜色设置为白色
        //估值为0
        //父结点为NULL
        //查找状态设置为1,表示找到了
        if (match((void *) pth_vertex_tmp, (void *) start)) {
            pth_vertex_tmp->color = white;
            pth_vertex_tmp->d = 0;
            pth_vertex_tmp->parent = NULL;
            found = 1;
        } else {
            //同时,将其他不是start的顶点进行初始设置
            //颜色白色
            //估值设置为DBL_MAX
            //parent为NULL
            pth_vertex_tmp->color = white;
            pth_vertex_tmp->d = DBL_MAX;
            pth_vertex_tmp->parent = NULL;
        }
    }

    //循环结束,判断查找状态是否为1,否:退出函数
    if (!found) {
        return -1;
    }

    //再次开始循环,遍历所有的graph顶点
    i = 0;
    while (i < graph_vcount(graph)) {
        //最小估值变量设置为DBL_MAX
        minimum = DBL_MAX;
        //循环遍历所有的顶点,
        //找到颜色为白色,并且顶点的最小估值小于最小估值的变量的值
        list_resetIterator(&graph_adjlists(graph));
        while (list_hasNext(&graph_adjlists(graph))) {
            list_moveToNext(&graph_adjlists(graph));
            list_iterator(&graph_adjlists(graph), (void **)&adjList_temp);
            pth_vertex_tmp = (PathVertex *)adjList_temp->vertex;
            if (pth_vertex_tmp->color == white && pth_vertex_tmp->d < minimum) {
                //重置最小估值变量为新值,
                //保存这个顶点
                minimum = pth_vertex_tmp->d;
                adjList = adjList_temp;
            }
        }

        //循环遍历结束,
        adj_vertex = (PathVertex *)adjList->vertex;
        //将找到的顶点设置为黑色
        adj_vertex->color = black;
        //循环遍历该顶点的所有邻接顶点链表中的顶点
        list_resetIterator(&(adjList->adjacent));
        while (list_hasNext(&(adjList->adjacent))) {
            list_moveToNext(&(adjList->adjacent));
            list_iterator(&(adjList->adjacent), (void **) (&pth_vertex_tmp));

            //循环遍历graph图中的所有顶点
            //将邻接顶点链表中的顶点与graph图中的顶点比对
            //如果匹配,调用relax函数
            list_resetIterator(&graph_adjlists(graph));
            while (list_hasNext(&graph_adjlists(graph))) {
                list_moveToNext(&graph_adjlists(graph));
                list_iterator(&graph_adjlists(graph), (void **)&adjList_temp);
                pth_vertex = (PathVertex *) adjList_temp->vertex;

                if (match(pth_vertex_tmp, pth_vertex)) {
                    //注意3个参数
                    relax(adj_vertex, pth_vertex, pth_vertex_tmp->weight);
                }
            }
        }
        i++;
    }//对该顶点的所有邻接顶点链表中的顶点的遍历结束

    list_init(paths, NULL);
    //初始化paths集合

    //遍历图中的所有顶点
    //如果顶点颜色为黑色
    //如果顶点插入到paths成功
    list_resetIterator(&graph_adjlists(graph));
    while (list_hasNext(&graph_adjlists(graph))) {
        list_moveToNext(&graph_adjlists(graph));
        list_iterator(&graph_adjlists(graph), (void **)&adjList_temp);
        pth_vertex_tmp = (PathVertex *) adjList_temp->vertex;

        if (pth_vertex_tmp->color == black) {
            if (list_ins_next(paths, list_tail(paths), pth_vertex_tmp) != 0) {
                list_destroy(paths);
                return -1;
            }
        }
    }
    return 0;
}

/***************************************************************************************************************/
/**
 * 旅行商问题
 *
 * @param vertices : vertices中的每个元素必须都是TspVertex类型。
 *                  TspVert.data来保存与顶点相关的数据，
 *                  TspVert.x, TspVertex.y  指定顶点的坐标。
 * tour中保存的顶点会按照路线中顶点的顺序排放。
 */
int tsp(List *vertices/*in*/,
        const TspVertex *start/*in*/,
        List *tour/*out*/,
        int (*match)(const void *key1, const void *key2)/*in*/) {

    //初始化tour集合
    list_init(tour, NULL);

    //found设置为0
    int found = 0;
    double x, y;
    TspVertex *start_in_vertices, *vertex_tmp, *vertex;

    //遍历集合vertices
    list_resetIterator(vertices);
    while (list_hasNext(vertices)) {
        list_moveToNext(vertices);
        list_iterator(vertices, (void **)(&vertex_tmp));

        //找到start元素，
        if (match(start, vertex_tmp)) {
            //先将其放入tour集合中，
            if (list_ins_next(tour, list_tail(tour), (void *)vertex_tmp) != 0) {
                list_destroy(tour);
                return -1;
            }

            //然后保存这个顶点, 以及其x，y的值
            start_in_vertices = vertex_tmp;
            x = vertex_tmp->x;
            y = vertex_tmp->y;
            //found设置为1
            found = 1;
            //将其颜色设置为黑色
            vertex_tmp->color = black;
        }else {
            //其他的顶点，颜色设置为白色
            vertex_tmp->color = white;
        }
    }

    //遍历完成
    //判断found不是1,则销毁tour, 退出函数
    if (!found) {
        list_destroy(tour);
        return -1;
    }

    int i = 0;
    double mininum;
    double distance = 0.0;
    //用i表示遍历的大小，i自加直到大于vertices的大小， 循环
    while(i< list_size(vertices) - 1){
        //设置mininum为DBL_MAX
        mininum = DBL_MAX;

        //遍历集合vertices
        list_resetIterator(vertices);
        while (list_hasNext(vertices)) {
            list_moveToNext(vertices);
            list_iterator(vertices, (void **)(&vertex_tmp));

            //如果顶点的颜色为白色,这样排除了那些加入到tour而且设置为黑色的那些顶点了
            if (vertex_tmp->color == white) {
                //计算其和保存的x,y的距离
                double tmp = pow(vertex_tmp->x - x, 2.0) + pow(vertex_tmp->y - y, 2.0);
                distance = sqrt(tmp);
                //如果距离小于mininum,则保存这个mininum,保存这个顶点
                if (distance < mininum){
                    mininum = distance;
                    vertex = vertex_tmp;
                }
            }
        }

        //遍历完成,那么在所有的白色顶点中就找到了距离上一个x,y的距离最小的顶点
        //设置x,y的值为保存的顶点的x,y的值
        x = vertex->x;
        y = vertex->y;
        //设置这个保存的顶点的颜色为黑色
        vertex->color = black;
        //将这个顶点加入到tour的尾部
        if (list_ins_next (tour, list_tail(tour), (void *)vertex) != 0){
            list_destroy(tour);
            return -1;
        }
        //i++，循环继续,如此循环list_size(vertices) - 1次
        i++;
    }

    //循环结束
    //再次将开始顶点加入到tour的尾部
    if (list_ins_next (tour, list_tail(tour), (void *)start_in_vertices) != 0){
        list_destroy(tour);
        return -1;
    }

    return 0;
}
