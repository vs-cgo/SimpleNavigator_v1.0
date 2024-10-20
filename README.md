# SimpleNavigator_v1.0

### Реализация библиотеки s21_graph:

  1. __LoadGraphFromFile(string filename)__ — загрузка графа из файла в формате матрицы смежности.
  2. __ExportGraphToDot(string filename)__ — выгрузка графа в файл в формате dot (см. материалы).

### Реализация библиотеки s21_graph_algorithms:
  
  1. __DepthFirstSearch(Graph &graph, int start_vertex)__ — нерекурентный поиск в глубину в графе от заданной вершины.
  2. __BreadthFirstSearch(Graph &graph, int start_vertex)__ — поиск в ширину в графе от заданной вершины.
  3. __GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)__ — поиск кратчайшего пути между двумя вершинами в графе с использованием алгоритма Дейкстры.
  4. __GetShortestPathsBetweenAllVertices(Graph &graph)__ — поиск кратчайших путей между всеми парами вершин в графе с использованием алгоритма Флойда-Уоршелла.
  5. __GetLeastSpanningTree(Graph &graph)__ — поиск наименьшего остовного дерева в графе с помощью алгоритма Прима.
