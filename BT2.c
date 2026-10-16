#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice device;
    struct EnergySensor sensor;
    float operatingHours;
    float totalKWh;
    float totalCost = 0;

    printf("=== NHAP THONG TIN THIET BI VA CAM BIEN ===\n");
    printf("Nhap ma dinh danh thiet bi (deviceID): ");
    scanf("%d", &device.deviceID);

    printf("Nhap ten thiet bi (deviceName): ");
    scanf("%s", device.deviceName);

    printf("Nhap trang thai hoat dong (1: Bat, 0: Tat): ");
    scanf("%d", &device.status);

    printf("Nhap cong suat dinh muc (ratedPowerKW): ");
    scanf("%f", &device.ratedPowerKW);

    printf("Nhap dien ngo vao (voltageVolts): ");
    scanf("%f", &sensor.voltageVolts);

    printf("Nhap dong dien do duoc (currentAmperes): ");
    scanf("%f", &sensor.currentAmperes);

    printf("Nhap thoi gian vang nguoi (unoccupancyMinutes): ");
    scanf("%d", &sensor.unoccupancyMinutes);

    printf("Nhap so gio van hanh trong thang (operatingHours): ");
    scanf("%f", &operatingHours);

    if (sensor.voltageVolts < 0 || sensor.currentAmperes < 0 || sensor.unoccupancyMinutes < 0) {
        printf("\n[LOI DU LIEU] Thong so cam bien khong hop le (gia tri am)!\n");
        return 1;
    }

    if (operatingHours <= 0 || operatingHours > 744) {
        printf("\n[LOI DU LIEU] So gio van hanh trong thang khong hop le (0 < hours <= 744)!\n");
        return 1;
    }

    if (sensor.currentAmperes > 30.0f) {
        device.status = 0;
        printf("\n[CANH BAO] Qua tai dong dien (>30.0A)! Kich hoạch ngat khan cap, da tat thiet bi.\n");
    } else if (device.status == 1 && sensor.unoccupancyMinutes >= 15) {
        device.status = 0;
        printf("\n[TIET KIEM NANG LUONG] Phong trong >= 15 phut, tu dong tat thiet bi.\n");
    }

    if (device.status == 1) {
        totalKWh = device.ratedPowerKW * operatingHours;
    } else {
        totalKWh = 0.0f;
    }

    if (totalKWh <= 50) {
        totalCost = totalKWh * 1806;
    } else if (totalKWh <= 100) {
        totalCost = 50 * 1806 + (totalKWh - 50) * 1866;
    } else if (totalKWh <= 200) {
        totalCost = 50 * 1806 + 50 * 1866 + (totalKWh - 100) * 2167;
    } else {
        totalCost = 50 * 1806 + 50 * 1866 + 100 * 2167 + (totalKWh - 200) * 2729;
    }

    printf("\n=================== BAO CAO HE THONG SMART HOME ===================\n");
    printf("%-12s %-15s %-10s %-15s\n", "MA THIET BI", "TEN THIET BI", "TRANG THAI", "CONG SUAT (kW)");
    printf("-------------------------------------------------------------------\n");
    printf("%-12d %-15s %-10s %-15.2f\n", 
           device.deviceID, 
           device.deviceName, 
           device.status == 1 ? "BAT" : "TAT", 
           device.ratedPowerKW);
    printf("-------------------------------------------------------------------\n");
    printf("Tong dien nang tieu thu: %.2f kWh\n", totalKWh);
    printf("Tong tien dien du kien (chua VAT): %.2f VNĐ\n", totalCost);

    return 0;
}