# SystemC_Group_21_final_project

## 預先安裝SystemC函式庫
1. 下載自github : https://github.com/accellera-official/systemc
2. 解壓縮後點擊開啟專案資料夾路徑 msvc10\SystemC
3. 開啟 SystemC.sln 並以 win32(x86) 建置
4. 完成後在 systemc\msvc10\SystemC\Debug 會產生 SystemC.lib 函式庫


## 設置SystemC路徑 (記得設置為32位元)

1. 右鍵專案 > 屬性(R)
2. 在 組態屬性 > C/C++ > 一般 > 其他 Include 目錄 新增 SystemC壓縮檔的 scr 項目
3. 在 組態屬性 > C/C++ > 語言 > 啟用執行階段類型資訊 > 變更為 "是 (/GR)"
4. 在 組態屬性 > C/C++ > 命令列 > 新增 "/vmg /D_CRT_SECURE_NO_DEPRECATE"
5. 在 組態屬性 > 連結器 > 一般 > 其他程式庫目錄 > 新增 SystemC壓縮檔的 debug 項目 (裡面應該有個SystemC.lib)
6. 在 組態屬性 > 連結器 > 輸入 > 其他相依性 > 新增 "SystemC.lib"
