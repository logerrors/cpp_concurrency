add_rules("mode.debug", "mode.release", "mode.asan")
set_languages("c++20")

add_requires("benchmark")

project_list = {
    "00_hello_world",
    "01_hello_world",
    "02_hello_world",
    "03_hello_world",

    "10_control_thread",
    "11_control_thread",
    "12_control_thread",
    "13_control_thread",
    "14_control_thread",

    "20_share_data",
    "21_share_data",
    "22_share_data",
    "23_share_data",
    "24_share_data",
    "25_share_data",
    "26_share_data",
    "27_share_data",
    "28_share_data",

    "30_sync_thread",
    "31_sync_thread",
    "32_sync_thread",
    "33_sync_thread",
    "34_sync_thread",
    "35_sync_thread",
    "36_sync_thread",

    "find",
    "find2",

    "40_atomic",
    "41_atomic",
    "42_atomic",
    "43_atomic",
    "44_atomic",
    "45_atomic",
    "46_atomic"
}

for _, project in pairs(project_list) do
    target(project)
    set_kind("binary")
    add_files(string.format("src/%s.cpp", project))
    if(project == "28_share_data") then
        add_packages("benchmark")
    end
    if(project == "40_atomic") then
        add_packages("benchmark")
    end
    add_syslinks("pthread")
end