# SystemC_Group_21_final_project

## 設置SystemC路徑 (記得設置為32位元)

1. 右鍵專案 > 屬性(R)
2. 在 組態屬性 > C/C++ > 一般 > 其他 Include 目錄 新增 SystemC壓縮檔的 scr 項目
3. 在 組態屬性 > C/C++ > 語言 > 啟用執行階段類型資訊 > 變更為 "是"
4. 在 組態屬性 > C/C++ > 命令列 > 新增 "/vmg /D_CRT_SECURE_NO_DEPRECATE"
5. 在 組態屬性 > 連結器 > 一般 > 其他程式庫目錄 > 新增 SystemC壓縮檔的 debug 項目 (裡面應該有個SystemC.lib)
6. 在 組態屬性 > 連結器 > 輸入 > 其他相依性 > 新增 "Systemc.lib"
