#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i;
int j;

struct CrudeOilData
{
    char crudeOilType[50];
    double harga[9];
};

void simpanKeFile(struct CrudeOilData *data, int entridata, const char *data_minyak_txt)
{
    FILE *file = fopen(data_minyak_txt, "w");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk save file.\n");
        return;
    }

    for (i = 0; i < entridata; i++)
    {
        fprintf(file, "%s ", data[i].crudeOilType);
        for (j = 0; j < 9; j++)
        {
            fprintf(file, "%.2lf ", data[i].harga[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void tampilkanTabelHeader()
{
    for (i = 0; i < 150; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("| %-20s |", "Crude Oil Type");
    for (i = 2004; i <= 2012; i++)
    {
        printf(" %-11d |", i);
    }
    printf("\n");
    for (i = 0; i < 150; i++)
    {
        printf("-");
    }
    printf("\n");
}

void tampilkanTabelFile(const char *data_minyak_txt)
{
    FILE *file = fopen(data_minyak_txt, "r");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk read file.\n");
        exit(1);
    }

    tampilkanTabelHeader();

    struct CrudeOilData crudeOilData;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "%s", crudeOilData.crudeOilType);
        printf("| %-20s |", crudeOilData.crudeOilType);

        char *hargaStart = strchr(line, ' ');
        if (hargaStart != NULL)
        {
            for (j = 0; j < 9; j++)
            {
                hargaStart = strchr(hargaStart, ' ');
                if (hargaStart != NULL)
                {
                    hargaStart++;
                    sscanf(hargaStart, "%lf", &crudeOilData.harga[j]);
                    printf(" %-11.2lf |", crudeOilData.harga[j]);
                }
            }
        }
        printf("\n");
    }

    fclose(file);
}

void readFromFile(struct CrudeOilData *data, int entridata, const char *data_minyak_txt)
{
    FILE *file = fopen(data_minyak_txt, "r");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk read file.\n");
        exit(1);
    }

    for (i = 0; i < entridata; i++)
    {
        fscanf(file, "%s", data[i].crudeOilType);
        for (j = 0; j < 9; j++)
        {
            fscanf(file, "%lf", &data[i].harga[j]);
        }
    }

    fclose(file);
}

void hitungAveragePerTahun(struct CrudeOilData *data, int entridata)
{
    for (i = 0; i < 150; i++)
    {
        printf("-");
    }
    printf("\n");

    printf("| %-20s |", "Average");
    for (i = 2004; i <= 2012; i++)
    {
        double total = 0;
        for (j = 0; j < entridata; j++)
        {
            total += data[j].harga[i - 2004];
        }
        double average = total / entridata;
        printf(" %-11.2lf |", average);
    }
    printf("\n");
    for (i = 0; i < 150; i++)
    {
        printf("-");
    }
    printf("\n");
}

void urutkanHarga(struct CrudeOilData *data, int entridata, int inputTahun)
{
    if (inputTahun < 2004 || inputTahun > 2012)
    {
        printf("Masukkan tahun antara 2004 dan 2012.\n");
        return;
    }

    for (i = 0; i < entridata - 1; i++)
    {
        for (j = 0; j < entridata - i - 1; j++)
        {
            if (data[j].harga[inputTahun - 2004] > data[j + 1].harga[inputTahun - 2004])
            {
                struct CrudeOilData temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    printf("\nData Crude Oil Type yang diurutkan berdasarkan harga untuk tahun %d\n", inputTahun);
    printf("%-18s%-10s\n", "Crude Oil Type", "Harga");
    printf("================================\n");

    for (i = 0; i < entridata; i++)
    {
        printf("%-18s$%-10.2lf\n", data[i].crudeOilType, data[i].harga[inputTahun - 2004]);
    }
}


void tampilkanDataType(struct CrudeOilData *data, int entridata)
{
    char userInput[50];
    printf("\nMasukkan Nama Crude Oil Type : ");
    scanf("%s", userInput);

    for (i = 0; i < entridata; i++)
    {
        if (strcmp(userInput, data[i].crudeOilType) == 0)
        {
            printf("\nData for Crude Oil Type '%s'\n", userInput);
            printf("%-10s%-18s%-10s\n", "Tahun", "Crude Oil Type", "Harga");
            printf("========================================\n");

            for (j = 0; j < 9; j++)
            {
                printf("%-10d%-18s$%-10.2lf\n", 2004 + j, data[i].crudeOilType, data[i].harga[j]);
            }
            return;
        }
    }

    printf("Crude Oil Type '%s' tidak ditemukan.\n", userInput);
}

void tampilkanHargaTertinggi(struct CrudeOilData *data, int entridata)
{
    printf("\nCrude Oil Type dengan Harga Tertinggi untuk Setiap Tahun\n");
    printf("%-10s%-18s%-10s\n", "Tahun", "Crude Oil Type", "Harga");
    printf("========================================\n");

    for (j = 0; j < 9; j++)
    {
        double highestPrice = data[0].harga[j];
        char highestType[50];
        strcpy(highestType, data[0].crudeOilType);

        for (i = 1; i < entridata; i++)
        {
            if (data[i].harga[j] > highestPrice)
            {
                highestPrice = data[i].harga[j];
                strcpy(highestType, data[i].crudeOilType);
            }
        }

        printf("%-10d%-18s$%-10.2lf\n", 2004 + j, highestType, highestPrice);
    }
}

void menu(struct CrudeOilData *data, int entridata)
{
    int pilih;
    printf("\nMenu:\n");
    printf("1. Urutan Harga Termahal Tahun Tertentu\n");
    printf("2. Harga Minyak Paling Mahal (2004-2012)\n");
    printf("3. Tampilkan Data Berdasarkan Crude Oil Type\n");
    printf("4. Keluar\n");
    printf("Pilih menu: ");
    scanf("%d", &pilih);

    switch (pilih)
    {
    case 1:
    {
        int inputTahun;
        printf("\nMasukkan tahun untuk pengurutan: ");
        scanf("%d", &inputTahun);
        urutkanHarga(data, entridata, inputTahun);
    }
    break;
    case 2:
        tampilkanHargaTertinggi(data, entridata);
        break;
    case 3:
        tampilkanDataType(data, entridata);
        break;
    case 4:
        printf("Program berhenti.\n");
        exit(0);
    default:
        printf("Pilihan tidak valid.\n");
    }
}

int main()
{
    const char *data_minyak_txt = "data_minyak.txt";
    struct CrudeOilData crudeOilArray[11];

    strcpy(crudeOilArray[0].crudeOilType, "SLC");
    double hargaSLC[] = {36.30, 53.92, 64.24, 72.94, 99.90, 64.14, 81.44, 113.63, 120.59};
    memcpy(crudeOilArray[0].harga, hargaSLC, sizeof(hargaSLC));

    strcpy(crudeOilArray[1].crudeOilType, "Arjuna");
    double hargaArjuna[] = {36.90, 55.07, 65.52, 72.38, 97.61, 61.18, 78.91, 112.47, 116.82};
    memcpy(crudeOilArray[1].harga, hargaArjuna, sizeof(hargaArjuna));

    strcpy(crudeOilArray[2].crudeOilType, "Arun-Condensate");
    double hargaArunCondensate[] = {37.40, 54.62, 64.85, 72.94, 94.27, 60.33, 78.76, 109.02, 111.28};
    memcpy(crudeOilArray[2].harga, hargaArunCondensate, sizeof(hargaArunCondensate));

    strcpy(crudeOilArray[3].crudeOilType, "Attaka");
    double hargaAttaka[] = {37.60, 57.51, 67.59, 75.69, 101.03, 62.74, 80.75, 114.38, 119.24};
    memcpy(crudeOilArray[3].harga, hargaAttaka, sizeof(hargaAttaka));

    strcpy(crudeOilArray[4].crudeOilType, "Cinta");
    double hargaCinta[] = {35.00, 51.81, 61.77, 70.33, 94.58, 59.74, 77.02, 110.50, 118.10};
    memcpy(crudeOilArray[4].harga, hargaCinta, sizeof(hargaCinta));

    strcpy(crudeOilArray[5].crudeOilType, "Duri");
    double hargaDuri[] = {30.40, 46.62, 54.93, 59.89, 84.57, 55.12, 75.07, 107.57, 117.19};
    memcpy(crudeOilArray[5].harga, hargaDuri, sizeof(hargaDuri));

    strcpy(crudeOilArray[6].crudeOilType, "Handil-Mix");
    double hargaHandilMix[] = {37.10, 55.23, 65.67, 72.53, 97.77, 61.33, 79.06, 112.62, 116.97};
    memcpy(crudeOilArray[6].harga, hargaHandilMix, sizeof(hargaHandilMix));

    strcpy(crudeOilArray[7].crudeOilType, "Lalang");
    double hargaLalang[] = {36.40, 53.13, 64.29, 72.99, 99.95, 64.19, 81.49, 113.68, 120.59};
    memcpy(crudeOilArray[7].harga, hargaLalang, sizeof(hargaLalang));

    strcpy(crudeOilArray[8].crudeOilType, "Widuri");
    double hargaWiduri[] = {35.00, 51.19, 61.94, 70.41, 94.98, 59.72, 77.12, 110.55, 118.49};
    memcpy(crudeOilArray[8].harga, hargaWiduri, sizeof(hargaWiduri));

    strcpy(crudeOilArray[9].crudeOilType, "Belida");
    double hargaBelida[] = {37.30, 56.54, 67.56, 75.71, 101.05, 62.30, 80.75, 114.14, 119.42};
    memcpy(crudeOilArray[9].harga, hargaBelida, sizeof(hargaBelida));

    strcpy(crudeOilArray[10].crudeOilType, "Senipah-Condensate");
    double hargaSenipahCondensate[] = {39.95, 54.62, 65.57, 73.03, 94.27, 60.33, 78.76, 109.02, 111.28};
    memcpy(crudeOilArray[10].harga, hargaSenipahCondensate, sizeof(hargaSenipahCondensate));

    simpanKeFile(crudeOilArray, 11, data_minyak_txt);
    readFromFile(crudeOilArray, 11, data_minyak_txt);
    tampilkanTabelFile(data_minyak_txt);
    hitungAveragePerTahun(crudeOilArray, 11);

    menu(crudeOilArray, 11);
    while (1)
    { 
        menu(crudeOilArray, 11);

        char yn;
        printf("\nApakah Anda ingin melanjutkan? (y/n): ");
        scanf(" %c", &yn);

        if (yn != 'y' && yn != 'Y')
        {
            printf("Program berhenti.\n");
            break; 
        }
    }

    return 0;
}