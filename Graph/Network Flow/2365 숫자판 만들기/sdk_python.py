INF = 9999999999
class Node:
    def __init__(self):
        self.edges, self.parent = [], None
        self.visited = False

class Edge:
    def __init__(self, fr, to, capacity):
        self.fr, self.to, self.capacity, self.flow = fr, to, capacity, 0
        self.pair = None

def data_in():
    return int( input()), list( map( int, input().split())), list( map( int, input().split()))

def connect_2nodes( fr, to, capacity):
    # edgeB is the residual edge
    edgeA, edgeB = Edge( fr, to, capacity), Edge( to, fr, 0)
    edgeA.pair = edgeB; edgeB.pair = edgeA
    fr.edges.append( edgeA)
    to.edges.append( edgeB)

def make_graph( max_capacity):
    source, sink = Node(), Node()
    middle_nodes = [[ Node() for _ in range( size)] for __ in range(size)]
    entrance_row_nodes, exit_col_nodes = [ Node() for _ in range(size)], [ Node() for __ in range( size)]

    # connect between source node and entrance row nodes
    for idx, node in enumerate( entrance_row_nodes):
        connect_2nodes( source, node, row_sum[idx])

    all_nodes = [source, sink]
    all_nodes.extend( entrance_row_nodes); all_nodes.extend( exit_col_nodes)
    for row in range( size):
        for col in range( size):
            # connect between entrance node and current node
            connect_2nodes( entrance_row_nodes[row], middle_nodes[row][col], max_capacity)
            # connect between current node and exit node
            connect_2nodes( middle_nodes[row][col], exit_col_nodes[col], max_capacity)

            all_nodes.append( middle_nodes[row][col])

    # connect between sink node and exit column nodes
    for idx, node in enumerate( exit_col_nodes):
        connect_2nodes( node, sink, col_sum[idx])
        all_nodes.append( node)

    return source, sink, all_nodes, entrance_row_nodes

def init_visited_nodes( nodes):
    for node in nodes : node.visited = False

def bfs( source, sink):
    queue, source.visited = [ source], True

    while len( queue) > 0:
        current=queue[0]; queue.pop(0);
        for edge in current.edges:
            if (not edge.to.visited) and (edge.capacity - edge.flow > 0) :
                queue.append( edge.to)
                edge.to.parent = edge
                edge.to.visited = True
                if edge.to == sink: return True

    return False

def get_path_N_flow( source, sink):
    path, current, min_flow = [], sink, INF
    while current != source:
        path.append( current.parent)
        min_flow = min( min_flow, current.parent.capacity - current.parent.flow)
        current = current.parent.fr

    return path, min_flow

def shed_flow(path, min_flow):
    for edge in path:
        edge.flow += min_flow
        edge.pair.flow -= min_flow

def revise_numbers( row_begin_nodes):
    numbers = []
    for row_begin_node in row_begin_nodes:
        unit = []
        for edge in row_begin_node.edges:
            unit.append( edge.flow)
        numbers.append( unit)

    return numbers

def solution( size):
    left, right = 0, max( max(row_sum), max(col_sum))
    expected_flow = sum( row_sum)
    answer, numbers = right, None

    # bin search
    while left <= right:
        mid = int( (left + right) / 2)
        source, sink, all_nodes, row_begin_nodes = make_graph( mid)
        total_flow = 0

        # network flow( max flow)
        while bfs( source, sink):
            path, min_flow = get_path_N_flow( source, sink)
            shed_flow(path, min_flow)
            total_flow += min_flow
            init_visited_nodes(all_nodes)

        if total_flow == expected_flow:
            right = mid - 1
            if answer > mid:
                answer, numbers = mid, revise_numbers( row_begin_nodes)
        else: left = mid + 1

    return answer, numbers

if __name__ == '__main__':
    global size, row_sum, col_sum

    size, row_sum, col_sum = data_in()
    answer, numbers = solution( size)

    print( answer)
    for row in range( size):
        for col in range(1, size + 1):
            print( numbers[row][col], end=' ')
        print()