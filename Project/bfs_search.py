from helpers.queue import Queue
from helpers.get_neighbors import get_neighbors
import time
import pygame


def bfs_search(snake, food):
    """
    Breadth-first search algorithm.
    """

    bfs_queue = Queue()
    visited = set()

    # Add the starting position to the queue
    # For the head we don't need to add the path

    bfs_queue.push((snake.get_head(), [snake.get_direction()]))

    while not bfs_queue.isEmpty():
        current = bfs_queue.pop()
        current_position, directions = current
        # print(current_position, directions)
        if current_position == food.get_position():
            print("food position", food.get_position())

            print("Found food")
            print("Directions: ", directions)
            snake.auto_move(directions)
            print("snake position", snake.get_head())
            return directions
            # break
        #     snake.auto_move(directions)
        #     snake.grow()
        #     food.despawn()
        #     food.spawn()
        #     time.sleep(20)
        #     return

        visited.add(current_position)
        count = 0
        for neighbor in get_neighbors(current_position, directions[-1], snake):
            if neighbor.get_position() not in visited:
                count += 1
                if(count == 4):
                    time.sleep(100)
                bfs_queue.push(
                    (neighbor.get_position(), directions + [neighbor.get_direction()]))
