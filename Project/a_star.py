from helpers.queue import Queue
from helpers.priority_queue import PriorityQueue
from helpers.get_neighbors import get_neighbors
import time
import pygame

# snake: snake object
# i : iterator to keep track of where food will be
def aStar_search(snake, food):
    global width, rows, snack, tempFood, startState

    def nullHeuristic(state, problem=None):
        # trivial heuristic
        return 0

    def manhattan_heuristic(position):
        # uses distance as a score for heuristic
        xy1 = position
        xy2 = food.get_position()
        return abs(xy1[0] - xy2[0]) + abs(xy1[1] - xy2[1])

    pq = PriorityQueue()  # fringe
    visited = set()
    pq.push((snake.getStartState(), [], 0), 0)

    while 1:
        if pq.isEmpty():
            break

        current, directions, costs = pq.pop() 
        if current not in visited:
            visited.add(current)
            if current == food.get_position():
                snake.grow()
                snake.auto_move(directions)
                directions[2].append(len(directions))
            for neighbor, direction, cost in snake.get_neighbors(current):
                if neighbor not in pq.heap:
                    if neighbor in visited:  # make sure child is not in visited so we don't go backwards
                        continue
                    hCost = costs + cost + manhattan_heuristic(neighbor)
                    pq.push((neighbor, directions + [direction], costs + cost), hCost)