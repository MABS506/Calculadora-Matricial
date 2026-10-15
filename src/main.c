/*
 *                                           │
 *       ███████████████████                 │  Sumadora de Matrices
 *            ╚══██╔══╝                      │  MABS
 *   ██╗   ██╗   ██║   ███╗   ██╗██╗         │  
 *   ██║   ██║   ██║   ████╗  ██║╚═╝██╗      │  Universidad Tecnica Nacional
 *   ██║   ██║   ██║   ██╔██╗ ██║██╗╚═╝██╗   │  Ingenieria Electronica
 *   ██║   ██║   ██║   ██║╚██╗██║╚═╝██╗╚═╝   │  Programación II (IEL-921)
 *   ╚██████╔╝   ██║   ██║ ╚████║██╗╚═╝      │  
 *    ╚═════╝    ╚═╝   ╚═╝  ╚═══╝╚═╝         │  13/10/2026
 *                                           │
 */



# include <stdio.h> 
# include <string.h> 
# include "freertos/FreeRTOS.h" 
# include "freertos/task.h" 
# include "esp_log.h" 

static const char *TAG = "matrix_calc"; 

// =======================================
// ■ 1) IMPRESIÓN DE VALORES DE LA MATRIZ 
// =======================================
void print_matrix(const char* name , float mat [2][2]) { 
    
    // Impresión de Valores de Matriz Cuadrada
    printf("%s:\n", name);
    printf("[%7.2f, %7.2f]\n", mat [0][0] , mat [0][1]); 
    printf("[%7.2f, %7.2f]\n\n", mat [1][0] , mat [1][1]);
} 

// ====================================================
// ■ 2) LECTURA DE PUERTO SERIAL Y EXTRACCIÓN DE DATOS 
// ====================================================
void read_serial_line(char* buffer , size_t max_len) {
    
    while (true) {
        
        // Eliminación del Carro de Texto
        if (fgets(buffer , max_len , stdin) != NULL) {
            buffer[strcspn(buffer , "\r")] = 0; 
            buffer[strcspn(buffer , "\n")] = 0;
            
            if (strlen(buffer) > 0) { 
                return; 
            }
        }

        vTaskDelay(pdMS_TO_TICKS (50)); // Ejecución de Codigo programado como tarea segun RTOS
    
    }
}

// ============================================
//  ■ 3) PROGRAMA PRINCIPAL (SUMA DE MATRICES) 
// ============================================
void app_main(void) {
    
    char rx_buffer [128];
    float A[2][2] , B[2][2] , Sum [2][2], Res[2][2];
    
    ESP_LOGI(TAG , "Operaciones Matriciales"); 
    
    while (true) { 

        // ========== Verificación de la Matriz A ==========
        printf("A? a11 a12 a21 a22: \n"); 
        read_serial_line(rx_buffer , sizeof(rx_buffer)); 
        
        // Determina si solo existen 4 Valores en a Matriz A
        if (sscanf(rx_buffer , "%f %f %f %f", &A[0][0] , &A[0][1] , &A[1][0] , &A [1][1]) != 4) {
            printf("Error en Matriz A.\n\n"); 
            continue;
        } 
       
        // ========== Verificación de la Matriz B ==========
        printf("B? b11 b12 b21 b22: \n"); 
        read_serial_line(rx_buffer , sizeof(rx_buffer)); 
        
        // Determina si solo existen 4 Valores en la Matriz B
        if (sscanf(rx_buffer , "%f %f %f %f", &B[0][0] , &B[0][1] , &B[1][0] , &B [1][1]) != 4) {
            printf("Error en Matriz B.\n\n"); 
            continue;
        }

        // ===== Impresión de Resultados =====
        printf("\n--- MATRICES ---\n"); 
        print_matrix("Matriz A", A); 
        print_matrix("Matriz B", B);
        printf("--- RESULTADOS ---\n");
        
        // 1.SUMA (A + B)
        Sum [0][0] = A[0][0] + B[0][0]; 
        Sum [0][1] = A[0][1] + B[0][1]; 
        Sum [1][0] = A[1][0] + B[1][0]; 
        Sum [1][1] = A[1][1] + B[1][1];
        print_matrix("Adición (A + B)", Sum);

        //2.RESTA (A - B)
        Res [0][0] = A[0][0] - B[0][0];
        Res [0][1] = A[0][1] - B[0][1];
        Res [1][0] = A[1][0] - B[1][0];
        Res [1][1] = A[1][1] - B[1][1];
        print_matrix("Substracción (A - B)", Res);
        
        printf("│====================================│\n\n");
    }
}
