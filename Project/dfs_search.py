from helpers.stack import Stack
from helpers.get_neighbors import get_neighbors
import time
import pygame


def dfs_search(snake, food):
    """
    Breadth-first search algorithm.
    """

    dfs_stack = Stack()
    visited = set()

    # Add the starting position to the queue
    # For the head we don't need to add the path

    dfs_stack.push((snake.get_head(), [snake.get_direction()]))

    while not dfs_stack.isEmpty():
        current = dfs_stack.pop()
        current_position, directions = current
        visited.add(current_position)

        if current_position == food.get_position():
            print("current_position", current_position)
            print("food position", food.get_position())
            print("Found food")
            # game.score += 1
            # snake.grow()
            # food.despawn()
            # food.spawn()
            directions = directions[1:]
            return directions

        for neighbor in get_neighbors(current_position, directions[len(directions) - 1], snake):
            if neighbor.get_position() not in visited:
                dfs_stack.push(
                    (neighbor.get_position(), directions + [neighbor.get_direction()]))
