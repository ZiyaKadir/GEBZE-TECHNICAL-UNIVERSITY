import cv2
import numpy as np
import math

def identity_matrix(size):
    identity = [[0 if i != j else 1 for j in range(size)] for i in range(size)]
    return identity

def inverse_matrix(A):
    n = len(A)
    augmented = [A[i] + identity_matrix(n)[i] for i in range(n)]

    for i in range(n):
        if augmented[i][i] == 0:
            for j in range(i + 1, n):
                if augmented[j][i] != 0:
                    augmented[i], augmented[j] = augmented[j], augmented[i]
                    break
            else:
                raise ValueError("Matrix is singular and cannot be inverted.")

        pivot = augmented[i][i]
        for j in range(2 * n):
            augmented[i][j] /= pivot

        for k in range(n):
            if k != i:
                factor = augmented[k][i]
                for j in range(2 * n):
                    augmented[k][j] -= factor * augmented[i][j]

    inverse = [row[n:] for row in augmented]
    return inverse

def matrix_multiplication(A, B):
    if len(A[0]) != len(B):
        raise ValueError("Number of columns in the first matrix must be equal to the number of rows in the second matrix.")
    result = [[0 for _ in range(len(B[0]))] for _ in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(A[0])):
                result[i][j] += A[i][k] * B[k][j]
    return result

def con_image_to_array(image):
    height, width, channels = image.shape
    array = [[[image[y, x, c] for c in range(channels)] for x in range(width)] for y in range(height)]
    return array

def create_empty_array(height, width, channels):
    return [[[0 for _ in range(channels)] for _ in range(width)] for _ in range(height)]

def con_array_to_image(array):
    height = len(array)
    width = len(array[0])
    channels = len(array[0][0])
    
    image = np.zeros((height, width, channels), np.uint8)
    for y in range(height):
        for x in range(width):
            for c in range(channels):
                image[y, x, c] = array[y][x][c]

    return image

def affine_transformation_forward(array, height, width, channels, transformation_matrix):
    
    cx = width / 2
    cy = height / 2

    cos_theta = abs(transformation_matrix[0][0])
    sin_theta_1 = abs(transformation_matrix[0][1])
    sin_theta_2 = abs(transformation_matrix[1][0])

    new_width = int(width * cos_theta + height * sin_theta_1)
    new_height = int(width * sin_theta_2 + height * cos_theta)

    cx_new = new_width / 2
    cy_new = new_height / 2

    transformed_array = create_empty_array(new_height, new_width, channels)

    for y in range(height):
        for x in range(width):

            x_shifted = x - cx
            y_shifted = y - cy

            dest_coords = matrix_multiplication(transformation_matrix, [[x_shifted], [y_shifted]])
            dest_x = dest_coords[0][0] + cx_new
            dest_y = dest_coords[1][0] + cy_new

            dest_x_int = int(round(dest_x))
            dest_y_int = int(round(dest_y))

            if 0 <= dest_x_int < new_width and 0 <= dest_y_int < new_height:
                for c in range(channels):
                    transformed_array[dest_y_int][dest_x_int][c] = array[y][x][c]

    return transformed_array


def affine_transformation_backward(array, height, width, channels, transformation_matrix):

    cx = width / 2
    cy = height / 2

    cos_theta = abs(transformation_matrix[0][0])
    sin_theta_1 = abs(transformation_matrix[0][1])
    sin_theta_2 = abs(transformation_matrix[1][0])

    new_width = int(width * cos_theta + height * sin_theta_1)
    new_height = int(width * sin_theta_2 + height * cos_theta)

    cx_new = new_width / 2
    cy_new = new_height / 2

    transformed_array = create_empty_array(new_height, new_width, channels)

    inverse = inverse_matrix(transformation_matrix)

    for y in range(new_height):
        for x in range(new_width):

            x_shifted = x - cx_new
            y_shifted = y - cy_new

            original_coords = matrix_multiplication(inverse, [[x_shifted], [y_shifted]])
            original_x = original_coords[0][0] + cx
            original_y = original_coords[1][0] + cy

            original_x_int = int(round(original_x))
            original_y_int = int(round(original_y))

            if 0 <= original_x_int < width and 0 <= original_y_int < height:
                for c in range(channels):
                    transformed_array[y][x][c] = array[original_y_int][original_x_int][c]

    return transformed_array


def affine_transformation_bilinear(array, height, width, channels, transformation_matrix):
    
    cx = width / 2
    cy = height / 2

    cos_theta = abs(transformation_matrix[0][0])
    sin_theta_1 = abs(transformation_matrix[0][1])
    sin_theta_2 = abs(transformation_matrix[1][0])

    new_width = int(width * cos_theta + height * sin_theta_1)
    new_height = int(width * sin_theta_2 + height * cos_theta)

    cx_new = new_width / 2
    cy_new = new_height / 2

    transformed_array = create_empty_array(new_height, new_width, channels)

    
    inverse = inverse_matrix(transformation_matrix)

    for y in range(new_height):
        for x in range(new_width):

            x_shifted = x - cx_new
            y_shifted = y - cy_new

            original_coords = matrix_multiplication(inverse, [[x_shifted], [y_shifted]])
            original_x = original_coords[0][0] + cx
            original_y = original_coords[1][0] + cy

            if 0 <= original_x < width - 1 and 0 <= original_y < height - 1:
                x0 = int(math.floor(original_x))
                x1 = x0 + 1
                y0 = int(math.floor(original_y))
                y1 = y0 + 1

                dx = original_x - x0
                dy = original_y - y0

                for c in range(channels):
                    f00 = array[y0][x0][c]
                    f10 = array[y0][x1][c]
                    f01 = array[y1][x0][c]
                    f11 = array[y1][x1][c]

                    interpolated_value = (f00 * (1 - dx) * (1 - dy) +
                                          f10 * dx * (1 - dy) +
                                          f01 * (1 - dx) * dy +
                                          f11 * dx * dy)

                    transformed_array[y][x][c] = int(round(interpolated_value))

    return transformed_array




def affine_transformation(array, height, width, channels, transformation_matrix):

    cx = width / 2
    cy = height / 2

    print(f"Transformation matrix elements type: {type(transformation_matrix[0][0])}")
    print(f"Transformation matrix: {transformation_matrix}")


    cos_theta = abs(transformation_matrix[0][0])
    sin_theta_1 = abs(transformation_matrix[0][1])
    sin_theta_2 = abs(transformation_matrix[1][0])

    print(f"Cos(theta): {cos_theta}, Sin(theta1): {sin_theta_1}, Sin(theta1): {sin_theta_2}")

    new_width = int(width * cos_theta + height * sin_theta_1)
    new_height = int(width * sin_theta_2 + height * cos_theta)


    transformed_array = create_empty_array(new_height, new_width, channels)

    inverse = inverse_matrix(transformation_matrix)

    for y in range(new_height):
        for x in range(new_width):

            x_shifted = x - new_width / 2
            y_shifted = y - new_height / 2

            original_coords = matrix_multiplication(inverse, [[x_shifted], [y_shifted]])
            original_x = original_coords[0][0] + cx
            original_y = original_coords[1][0] + cy

            original_x_int = int(round(original_x))
            original_y_int = int(round(original_y))

            if 0 <= original_x_int < width and 0 <= original_y_int < height:
                for c in range(channels):
                    transformed_array[y][x][c] = array[original_y_int][original_x_int][c]

    return transformed_array

def main():
    image = cv2.imread("istanbul.jpg")
    height, width, channels = image.shape
    print(f"Width: {width}, Height: {height}")

    array = con_image_to_array(image)

    angle = 60 # degrees
    theta = math.radians(angle)
    

    # Build rotation matrix
    # affine_matrix = [
    #     [math.cos(theta), -math.sin(theta)],
    #     [math.sin(theta), math.cos(theta)]
    # ]

    # Identity matrix
    # affine_matrix = [
    #     [1, 0],
    #     [0, 1]
    # ]

    # Scaling matrix
    # affine_matrix = [
    #     [1.5, 0],
    #     [0, 1.5]
    # ]

    # Shearing Horizental matrix
    affine_matrix = [
        [1, 1.4],
        [0, 1]
    ]

    # Shearing Vertical matrix
    # affine_matrix = [
    #     [1, 0],
    #     [0.5, 1]
    # ]


    result = affine_transformation_bilinear(array, height, width, channels, affine_matrix)
    result_image = con_array_to_image(result)

    cv2.imshow("Original Image", image)
    print(image.shape)


    cv2.imshow("Affine Transformed Image", result_image)
    print(result_image.shape)

    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
