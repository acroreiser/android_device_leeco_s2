/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Helpers.h"
#include <regex>
#include <vector>
using namespace android::hardware::radio;

V1_4::SignalStrength Create1_4SignalStrength(const V1_0::SignalStrength& sigStrength){

    V1_4::SignalStrength newSigStrength = {};
    newSigStrength.gsm = sigStrength.gw;
    newSigStrength.cdma = sigStrength.cdma;
    newSigStrength.evdo = sigStrength.evdo;
    newSigStrength.lte = sigStrength.lte;

    newSigStrength.tdscdma.signalStrength = INT_MAX;
    newSigStrength.tdscdma.bitErrorRate = INT_MAX;
    newSigStrength.tdscdma.rscp = sigStrength.tdScdma.rscp != INT_MAX ?
        -sigStrength.tdScdma.rscp + 120 : INT_MAX;

    newSigStrength.wcdma.base.signalStrength = INT_MAX;
    newSigStrength.wcdma.base.bitErrorRate = INT_MAX;
    newSigStrength.wcdma.rscp = INT_MAX;
    newSigStrength.wcdma.ecno = INT_MAX;

    newSigStrength.nr.ssRsrp = INT_MAX;
    newSigStrength.nr.ssRsrq = INT_MAX;
    newSigStrength.nr.ssSinr = INT_MAX;
    newSigStrength.nr.csiRsrp = INT_MAX;
    newSigStrength.nr.csiRsrq = INT_MAX;
    newSigStrength.nr.csiSinr = INT_MAX;

    return newSigStrength;
}

V1_4::SignalStrength Create1_4SignalStrength(const V1_2::SignalStrength& sigStrength){

    V1_4::SignalStrength newSigStrength = {};
    newSigStrength.gsm = sigStrength.gsm;
    newSigStrength.cdma = sigStrength.cdma;
    newSigStrength.evdo = sigStrength.evdo;
    newSigStrength.lte = sigStrength.lte;
    newSigStrength.wcdma = sigStrength.wcdma;

    newSigStrength.tdscdma.signalStrength = INT_MAX;
    newSigStrength.tdscdma.bitErrorRate = INT_MAX;
    newSigStrength.tdscdma.rscp = sigStrength.tdScdma.rscp != INT_MAX ?
        -sigStrength.tdScdma.rscp + 120 : INT_MAX;

    newSigStrength.nr.ssRsrp = INT_MAX;
    newSigStrength.nr.ssRsrq = INT_MAX;
    newSigStrength.nr.ssSinr = INT_MAX;
    newSigStrength.nr.csiRsrp = INT_MAX;
    newSigStrength.nr.csiRsrq = INT_MAX;
    newSigStrength.nr.csiSinr = INT_MAX;

    return newSigStrength;
}

hidl_vec<V1_4::CellInfo> Create1_4CellInfoList(const hidl_vec<V1_0::CellInfo>& cellInfo) {
    hidl_vec<V1_4::CellInfo> newCI;
    newCI.resize(cellInfo.size());

    for(int x = 0; x < cellInfo.size(); ++x){
        newCI[x].isRegistered = cellInfo[x].registered;
        newCI[x].connectionStatus = (V1_2::CellConnectionStatus) INT_MAX;
        if(cellInfo[x].gsm.size() == 1){
            V1_2::CellInfoGsm GsmInfo = {};
            GsmInfo.cellIdentityGsm.base = cellInfo[x].gsm[0].cellIdentityGsm;
            GsmInfo.cellIdentityGsm.base.arfcn = INT_MAX;
            GsmInfo.cellIdentityGsm.base.bsic = 0xFF;

            std::string mnc = GsmInfo.cellIdentityGsm.base.mnc;
            if (mnc.length() == 1) {
                GsmInfo.cellIdentityGsm.base.mnc = "0" + mnc;
            }

            GsmInfo.signalStrengthGsm = cellInfo[x].gsm[0].signalStrengthGsm;
            GsmInfo.signalStrengthGsm.signalStrength = cellInfo[x].gsm[0].cellIdentityGsm.arfcn;
            GsmInfo.signalStrengthGsm.bitErrorRate = cellInfo[x].gsm[0].cellIdentityGsm.bsic;

            newCI[x].info.gsm(GsmInfo);
        }
        else if(cellInfo[x].cdma.size() == 1){
            V1_2::CellInfoCdma CdmaInfo = {};
            CdmaInfo.cellIdentityCdma.base = cellInfo[x].cdma[0].cellIdentityCdma;
            CdmaInfo.signalStrengthCdma = cellInfo[x].cdma[0].signalStrengthCdma;
            CdmaInfo.signalStrengthEvdo = cellInfo[x].cdma[0].signalStrengthEvdo;
            newCI[x].info.cdma(CdmaInfo);
        }
        else if(cellInfo[x].lte.size() == 1){
            V1_4::CellInfoLte LteInfo = {};
            LteInfo.base.cellIdentityLte.base = cellInfo[x].lte[0].cellIdentityLte;
            LteInfo.base.cellIdentityLte.base.earfcn = INT_MAX;
            LteInfo.base.cellIdentityLte.bandwidth = INT_MAX;
            LteInfo.cellConfig.isEndcAvailable = false;

            std::string mnc = LteInfo.base.cellIdentityLte.base.mnc;
            if (mnc.length() == 1) {
                LteInfo.base.cellIdentityLte.base.mnc = "0" + mnc;
            }

            LteInfo.base.signalStrengthLte.signalStrength = cellInfo[x].lte[0].cellIdentityLte.earfcn;

            LteInfo.base.signalStrengthLte.rsrp = cellInfo[x].lte[0].signalStrengthLte.signalStrength;
            LteInfo.base.signalStrengthLte.rsrq = cellInfo[x].lte[0].signalStrengthLte.rsrp;
            LteInfo.base.signalStrengthLte.rssnr = INT_MAX;
            LteInfo.base.signalStrengthLte.cqi = INT_MAX;
            LteInfo.base.signalStrengthLte.timingAdvance = INT_MAX;

            newCI[x].info.lte(LteInfo);
        }
        else if(cellInfo[x].wcdma.size() == 1){
            V1_2::CellInfoWcdma WcdmaInfo = {};
            WcdmaInfo.cellIdentityWcdma.base = cellInfo[x].wcdma[0].cellIdentityWcdma;
            WcdmaInfo.cellIdentityWcdma.base.uarfcn = INT_MAX;

            std::string mnc = WcdmaInfo.cellIdentityWcdma.base.mnc;
            if (mnc.length() == 1) {
                WcdmaInfo.cellIdentityWcdma.base.mnc = "0" + mnc;
            }

            WcdmaInfo.signalStrengthWcdma.base.signalStrength = cellInfo[x].wcdma[0].cellIdentityWcdma.uarfcn;
            WcdmaInfo.signalStrengthWcdma.base.bitErrorRate = cellInfo[x].wcdma[0].signalStrengthWcdma.signalStrength;

            WcdmaInfo.signalStrengthWcdma.rscp = 2 * WcdmaInfo.signalStrengthWcdma.base.signalStrength + 7;
            WcdmaInfo.signalStrengthWcdma.ecno = INT_MAX;

            newCI[x].info.wcdma(WcdmaInfo);
        }
        else if(cellInfo[x].tdscdma.size() == 1){
            V1_2::CellInfoTdscdma TdscdmaInfo = {};
            TdscdmaInfo.cellIdentityTdscdma.base = cellInfo[x].tdscdma[0].cellIdentityTdscdma;
            TdscdmaInfo.cellIdentityTdscdma.uarfcn = INT_MAX;
            TdscdmaInfo.signalStrengthTdscdma.signalStrength = INT_MAX;
            TdscdmaInfo.signalStrengthTdscdma.bitErrorRate = INT_MAX;
            TdscdmaInfo.signalStrengthTdscdma.rscp = cellInfo[x].tdscdma[0].signalStrengthTdscdma.rscp != INT_MAX ?
                -cellInfo[x].tdscdma[0].signalStrengthTdscdma.rscp + 120 : INT_MAX;
            newCI[x].info.tdscdma(TdscdmaInfo);
        }
    }

    return newCI;
}

hidl_vec<V1_4::CellInfo> Create1_4CellInfoList(const hidl_vec<V1_2::CellInfo>& cellInfo) {
    hidl_vec<V1_4::CellInfo> newCI;
    newCI.resize(cellInfo.size());

    for(int x = 0; x < cellInfo.size(); ++x){
        newCI[x].isRegistered = cellInfo[x].registered;
        newCI[x].connectionStatus = cellInfo[x].connectionStatus;
        if(cellInfo[x].gsm.size() == 1)
            newCI[x].info.gsm(cellInfo[x].gsm[0]);

        else if(cellInfo[x].cdma.size() == 1)
            newCI[x].info.cdma(cellInfo[x].cdma[0]);

        else if(cellInfo[x].lte.size() == 1){
            V1_4::CellInfoLte LteInfo = {};
            LteInfo.base = cellInfo[x].lte[0];
            LteInfo.cellConfig.isEndcAvailable = false;
            newCI[x].info.lte(LteInfo);
        }
        else if(cellInfo[x].wcdma.size() == 1)
            newCI[x].info.wcdma(cellInfo[x].wcdma[0]);

        else if(cellInfo[x].tdscdma.size() == 1)
            newCI[x].info.tdscdma(cellInfo[x].tdscdma[0]);
    }

    return newCI;
}

hidl_vec<hidl_string> DelimitedStrToVec(std::string delimitedStr){
    std::regex rgx("\\s+");
    std::sregex_token_iterator iter(delimitedStr.begin(), delimitedStr.end(), rgx, -1);
    std::sregex_token_iterator end;

    std::vector<hidl_string> tokens;
    for ( ; iter != end; ++iter)
        tokens.push_back(hidl_string(*iter));

    return hidl_vec(tokens);
}

V1_4::SetupDataCallResult Create1_4SetupDataCallResult(const V1_0::SetupDataCallResult& dcResponse){
    V1_4::SetupDataCallResult newDCR = {};
    newDCR.cause = (V1_4::DataCallFailCause) dcResponse.status;
    newDCR.suggestedRetryTime = dcResponse.suggestedRetryTime;
    newDCR.cid = dcResponse.cid;
    newDCR.active = (V1_4::DataConnActiveStatus) dcResponse.active;
    newDCR.ifname = dcResponse.ifname;
    newDCR.mtu = dcResponse.mtu;
    newDCR.addresses = DelimitedStrToVec(dcResponse.addresses);
    newDCR.dnses = DelimitedStrToVec(dcResponse.dnses);
    newDCR.gateways = DelimitedStrToVec(dcResponse.gateways);
    newDCR.pcscf = DelimitedStrToVec(dcResponse.pcscf);
    if(dcResponse.type == std::string("IP"))
        newDCR.type= V1_4::PdpProtocolType::IP;
    else if(dcResponse.type == std::string("IPV6"))
        newDCR.type= V1_4::PdpProtocolType::IPV6;
    else if(dcResponse.type == std::string("IPV4V6"))
        newDCR.type= V1_4::PdpProtocolType::IPV4V6;
    else if(dcResponse.type == std::string("PPP"))
        newDCR.type= V1_4::PdpProtocolType::PPP;
    else if(dcResponse.type == std::string("NON-IP"))
        newDCR.type= V1_4::PdpProtocolType::NON_IP;
    else if(dcResponse.type == std::string("UNSTRUCTURED"))
        newDCR.type= V1_4::PdpProtocolType::UNSTRUCTURED;
    else
        newDCR.type= V1_4::PdpProtocolType::UNKNOWN;

    return newDCR;
}
