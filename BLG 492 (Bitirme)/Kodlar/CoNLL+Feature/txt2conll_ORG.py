# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import io
import re

inFileName = 'KapAciklamalari.txt'
outFileName = 'etiketlenenKapAciklamalari.txt'

regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"

orgWords = ['A.O.', 'A.V.O.D.', 'A.Ş.', 'ACIPAYAM', 'ACISELSAN', 'ADANA', 'ADEL', 'ADESE', 'AE', 'AFYON', 'AG',
            'AK', 'AKBANK', 'AKDENİZ', 'AKENERJİ', 'AKFEN', 'AKILLI', 'AKIN', 'AKKARDAN', 'AKMERKEZ', 'AKRİLİK', 'AKSA', 'AKSU', 'AKSİGORTA', 'AKTIENGESELLSCHAFT', 'AKYÜREK', 'AKÇANSA', 'AKİŞ',
            'ALARKO', 'ALBARAKA', 'ALCATEL', 'ALETLERİ', 'ALIŞVERİŞ', 'ALJ', 'ALKALİ', 'ALKİM', 'ALTERNATİF', 'ALTERNATİFBANK', 'ALTIN', 'ALTINYAĞ', 'ALTINYUNUS', 'ALÜMİNYUM',
            'AMBALAJ', 'ANADOLU', 'ANALİZ', 'ANEL', 'ANKASTRE', 'ANONİM', 'ARAÇ', 'ARAŞTIRMA', 'ARENA', 'ARMA', 'ARMADA', 'ARSAN', 'ARTI', 'ARZUM', 'ARÇELİK',
            'ASELSAN', 'ASLAN', 'ASYANET', 'ATA', 'ATAKULE', 'ATILIM', 'ATLANTİK', 'ATLANTİS', 'ATLAS', 'AVRASYA', 'AVRUPA', 'AVİVASA', 'AYAKKABI', 'AYEN', 'AYES', 'AYGAZ',
            'BAGFAŞ', 'BAK', 'BAKIR', 'BALATACILAR', 'BALATACILIK', 'BANDIRMA', 'BANK', 'BANKASI', 'BANTAŞ', 'BANVİT', 'BAROMETRE', 'BASIM', 'BATI', 'BATISÖKE', 'BATIÇİM', 'BAŞBAKANLIK', 'BAŞER', 'BAŞKANLIĞI', 'BAŞKENT', 'BAŞTAŞ',
            'BDO', 'BEMKA', 'BERA', 'BEREKET', 'BERKOSAN', 'BESİ', 'BESİCİLİK', 'BETON', 'BEYAZ', 'BEŞİKTAŞ',
            'BNO', 'BOBİN', 'BOLU', 'BOMONTİ', 'BORU', 'BORUSAN', 'BOSCH', 'BOSSA', 'BOYA', 'BOYNER', 'BRIDGESTONE', 'BRİSA', 'BURDA', 'BURSA', 'BURÇELİK',
            'BÖLGESİ', 'BİLGİSAYAR', 'BİLİCİ', 'BİM', 'BİMEKS', 'BİRA', 'BİRACILIK', 'BİRKO', 'BİRLEŞİK', 'BİRLİK', 'BİS', 'BİSKÜVİ', 'BİYOLOJİK', 'BİZİM',
            'CAM', 'CARREFOUR', 'CARREFOURSA', 'CARRIER', 'CO', 'COCA-COLA', 'COMPONENTA', 'COSMOS', 'CREDITWEST',
            'DAGİ', 'DANIŞMANLIK', 'DARDANEL', 'DATAGATE', 'DAYANIKLI', 'DEKORASYON', 'DEMİR', 'DEMİSAŞ',
            'DENET', 'DENGE', 'DENİZ', 'DENİZBANK', 'DENİZCİLİK', 'DENİZLİ', 'DEPOSU', 'DERGİ', 'DERİ', 'DERİMOD', 'DERİNDERE', 'DESA', 'DESPEC', 'DESTEK', 'DEUTSCHE', 'DEVA', 'DEĞERLER',
            'DIŞ', 'DO', 'DONANIMI', 'DORUK', 'DOĞAL', 'DOĞAN', 'DOĞTAŞ', 'DOĞUSAN', 'DOĞUŞ', 'DURAN', 'DYO', 'DÖKÜM', 'DÖKÜMCÜLÜK', 'DİJİTAL', 'DİRİLİŞ', 'DİRİTEKS', 'DİTAŞ',
            'ECZA', 'ECZACIBAŞI', 'EDİP', 'EFES', 'EGE', 'EGELİ', 'EGEPLAST', 'EKO', 'EKONOMİ', 'EKSPO', 'EKİM', 'EKİPMAN', 'EKİZ',
            'ELEKTROLİTİK', 'ELEKTROMEKANİK', 'ELEKTRONİK', 'ELEKTROPANÇ', 'ELEKTRİK', 'ELEKTRİKLİ', 'ELEMANLARI', 'ELYAF', 'EMAY', 'EMAYE', 'EMEK', 'EMEKLİLİK', 'EMLAK', 'EMİNİŞ',
            'ENDÜSTRİ', 'ENDÜSTRİSİ', 'ENDÜSTRİYEL', 'ENERJİ', 'ENERJİSA', 'ENET', 'ENGÜRÜSAĞ', 'ENKA', 'ENTEGRE',
            'ERBOSAN', 'ERCİYAS', 'EREĞLİ', 'ERSU', 'ESCORT', 'ESEM', 'ET', 'ETİLER', 'EURO', 'EV', 'EĞİTİM', 'EİS', 'EŞYA',
            'FABRİKALARI', 'FABRİKASI', 'FAKTORİNG', 'FEDERAL-MOGUL', 'FENERBAHÇE', 'FIAT','FIRÇA', 'FLAP',
            'FONET', 'FORD', 'FREN', 'FRİGO-PAK', 'FUTBOL', 'FİBA', 'FİBABANKA', 'FİLAMENT', 'FİLO','FİNAL', 'FİNANS', 'FİNANSBANK', 'FİNANSMAN',
            'GALATASARAY', 'GARANTİ', 'GAYRİMENKUL', 'GAZETECİLİK', 'GEDİK', 'GEDİZ', 'GELİŞTİRME', 'GENTAŞ', 'GERSAN', 'GIDA', 'GLOBAL', 'GLOKAL', 
            'GOODYEAR','GRUBU', 'GSD', 'GÖLLER', 'GÖLTAŞ', 'GÖZDE', 'GÜBRE', 'GÜLER', 'GÜMÜŞ', 'GÜNEŞ', 'GÜVEN', 'GÜVENLİK', 'GİMAT','GİRİŞİM', 'GİYİM', 'GYO',
            'HACI', 'HALAT', 'HALI', 'HALİKARNAS', 'HALK', 'HASAT', 'HASIR', 'HATAY', 'HATEKS', 'HAVA', 'HAVALİMANLARI', 'HAYAT', 'HAYVANCILIK', 'HAZIR', 'HAZIRBETON',
            'HEDEF', 'HEKTAŞ', 'HEKİM', 'HOLDING', 'HOLDİNG', 'HUZUR', 'HÜRRİYET','HİZMETLERİ',
            'IC', 'ICBC', 'ING', 'INTERNATIONAL', 'ISUZU', 'IŞIKLAR',
            'JANT', 'JANTSA',
            'KABLO','KADİFE', 'KALEBODUR', 'KALEMCİLİK', 'KALESERAMİK', 'KALKINMA', 'KAPLAMİN', 'KAPİTAL', 'KARABÜK','KARADENİZ', 'KARDEMİR', 'KAREL', 'KARSAN', 'KARSU', 'KARSUSAN', 'KART', 'KARTON', 'KARTONSAN',
            'KATILIM','KATMERCİLER', 'KAYNAKLARI', 'KAĞIT', 'KAĞITÇILIK', 'KELEBEK', 'KENT', 'KEREVİTAŞ', 'KERVANSARAY', 'KIRTASİYE', 'KIRTASİYECİLİK', 'KIYMET', 'KIYMETLER', 'KLİMA', 'KLİMASAN',
            'KOLA', 'KOMBİNALARI', 'KONFEKSİYON', 'KONFRUT', 'KONGRE', 'KONUT', 'KONYA', 'KORAY', 'KORDSA', 'KORTEKS', 'KOTON', 'KOYUNLULULAR', 'KOZA', 'KOÇ', 'KOÇTAŞ',
            'KREDİ', 'KRON', 'KRİSTAL', 'KT', 'KURU', 'KURUTULMUŞ', 'KUTSAN', 'KUYUMCUKENT', 'KUŞADASI', 'KUŞTUR', 'KÖPÜK', 'KÖRFEZ', 'KÜTAHYA', 'KİLER', 'KİMYA', 'KİPA', 'KİRA', 'KİRALAMA',
            'LABORATUVARLARI', 'LASTİK', 'LASTİKLERİ', 'LDR', 'LİMAK', 'LOGO', 'LOJİSTİK', 'LOKMAN', 'LUCENT', 'LÜKS', 'LİDER', 'LIMAK', 'LİMAN', 'LİNK', 'LTD',
            'MADENCİLİK', 'MAHSULLERİ', 'MAK', 'MAKİNA', 'MAKİNELERİ', 'MALLARI', 'MALT', 'MALZEMELERİ', 'MAMULLERİ', 'MAMÜLLERİ', 'MANNESMANN',
            'MARDİN', 'MARKA', 'MARKETLERİ', 'MARMARİS', 'MARSHALL', 'MARTI', 'MATBAACILIK', 'MAVERA', 'MAVİ', 'MAZHAR', 'MAĞAZACILIK', 'MAĞAZALAR', 'MAĞAZALARI',
            'MCT', 'MEGA', 'MENDERES', 'MENKUL', 'MENSUCAT', 'MEPET', 'MERKEZLERİ', 'MERKEZİ', 'MERKO', 'MERİT',
            'METAL', 'METEMTUR', 'METRO', 'MEYVE', 'MEŞRUBAT', 'MLP', 'MMC', 'MOBİLYA', 'MONDİ', 'MOTOR', 'MÜHENDİSLİK', 'MÜŞAVİRLİK', 'MİGROS', 'MİLPA', 'MİSH', 'MİSTRAL',
            'NET', 'NETEL', 'NETAŞ', 'NETLOG', 'NOBEL', 'NUH', 'NUROL', 'NİĞBAŞ', 'NİĞDE',
            'ODAŞ', 'OLMUKSAN', 'OPET', 'OPTİMA', 'ORFİN', 'ORGE', 'ORMA', 'ORMAN', 'ORTAKLIĞI', 'OSMANGAZİ', 'OSMANLI', 'OSTİM', 'OTEL', 'OTELCİLİK', 'OTO', 'OTOKAR', 'OTOKOÇ', 'OTOMOBİL', 'OTOMOTİV', 'OYAK', 'OYLUM',
            'PALMET', 'PAMUKLU', 'PANORA', 'PAPER', 'PARK', 'PARSAN', 'PARÇA', 'PARÇALARI', 'PASHA', 'PAZARLAMA',
            'PEGASUS', 'PEKER', 'PENGUEN', 'PERA', 'PERAKENDE', 'PERGAMON', 'PETKİM', 'PETROKENT', 'PETROKİMYA', 'PETROL', 'PETROLCÜLÜK',
            'PINAR', 'PLASTİK', 'PLASTİKKART', 'POLYESTER', 'POLİETİLEN', 'POLİMER', 'POLİSAN', 'POLİTEKNİK', 'PORSELEN', 'POZİTİF', 'PREFABRİK', 'PRES', 'PROFİL', 'PROJE', 'PROJESİ', 'PRYSMİAN', 'PRİZMA', 'PİM', 'PİMAŞ', 'PİRAMİT', 'PİSTON',
            'QNB',
            'RAFİNERİLERİ', 'RAL', 'RAY', 'REKLAMCILIK', 'REYSAŞ', 'RHEA', 'RODRİGO', 'ROYAL', 'RTA', 'RÖNESANS',
            'SABANCI', 'SAF', 'SAFKAR', 'SALİX', 'SAN-EL', 'SANAYI', 'SANAYİ', 'SANAYİİ', 'SANKO', 'SANİFOAM', 'SARAY', 'SARDES', 'SARKUYSAN', 'SARTEN', 'SASA', 'SATIŞ', 'SAVUNMA', 'SAY', 'SAĞLIK',
            'SEKURO', 'SELÇUK', 'SELÜLOZ', 'SENKRON', 'SENTETİK', 'SERAMİK', 'SERMAYESİ', 'SERTİFİKALARI', 'SERVE', 'SERVET', 'SERVİS', 'SERVİSİ', 'SEYİTLER',
            'SINAİ', 'SİLVER', 'SODA', 'SODAŞ', 'SODYUM', 'SOĞUK', 'SOĞUTMACILIK', 'SPOR', 'SPORTİF', 'STATUS', 'SU', 'SUKUK', 'SUMAŞ', 'SUNİ', 'SUNSET', 
            'SÖKE', 'SÖKTAŞ', 'SÖNMEZ', 'SÜMER', 'SÜNGER', 'SÜT', 'SİGORTA', 'SİLVERLİNE', 'SİNPAŞ', 'SİSTEMLERİ',
            'T.A.O.', 'T.A.Ş', 'TAAHHÜT', 'TAHTA', 'TAKIM', 'TAM', 'TARBES', 'TARIM', 'TAT', 'TAV', 'TAZE', 'TAÇ', 'TAŞIMACILIK', 'TAŞIMACILIĞI',
            'TEB', 'TECRİT', 'TEK-ART', 'TEKFEN', 'TEKNOLOJİ', 'TEKNOLOJİLERİ', 'TEKNOSA', 'TEKNİK', 'TEKSTİL', 'TEL', 'TELEKOMÜNİKASYON', 'TELETAŞ', 'TELİ', 'TEMAPOL', 'TERA', 'TEST', 'TESİSAT', 'TESİSLER', 'TESİSLERİ',
            'TF', 'TGS', 'TOFAŞ', 'TOPLU', 'TOPTAN', 'TORUNLAR', 'TRABZON', 'TRABZONSPOR', 'TRAKTÖR', 'TRAKYA', 'TRANSTÜRK', 'TREND', 'TRN', 'TSKB',
            'TUBORG', 'TUKAŞ', 'TURCAS', 'TURKCELL', 'TURKEY', 'TURKISH', 'TURİSTİK', 'TURİZM', 'TUĞÇELİK', 'TÜKETİM', 'TÜMOSAN', 'TÜPRAŞ-TÜRKİYE', 'TÜRKER', 'TİMUR', 'TİRE',
            'UFUK', 'ULAŞLAR', 'ULUSAL', 'ULUSOY', 'UMPAŞ', 'USAŞ', 'UTOPYA', 'UZERTAŞ', 'UŞAK',
            'VAKIF', 'VAKIFLAR', 'VAKKO', 'VANA', 'VANET', 'VARLIK', 'VERA', 'VERNİK', 'VERUSA', 'VERUSATURK', 'VESTEL', 'VETAŞ', 'VETERİNER', 'VOLKSWAGEN', 'VİKİNG', 'VİTAMİNLİ',
            'YALITIM', 'YAPI', 'YAPRAK', 'YATAK', 'YATAŞ', 'YATIRIM', 'YATIRIMLAR', 'YATIRIMLARI', 'YAYIN', 'YAYINCILIK', 'YAYLA', 'YAZILIM', 'YAZILIMI',
            'YDA', 'YEDEK', 'YEDİTEPE', 'YEM', 'YEŞİL', 'YOLLARI', 'YONGA', 'YORGAN', 'YOZGAT', 'YUNUS', 'YÜNLÜ', 'YÜNSA', 'YİBİTAŞ',
            'ZORLU', 'ZİRAAT',
            'ÇALIK','ÇANAKKALE', 'ÇAĞDAŞ', 'ÇELEBİ', 'ÇELİK', 'ÇEMAŞ', 'ÇEMTAŞ', 'ÇEŞME', 'ÇUHADAROĞLU', 'ÇİFTLİKLERİ','ÇİMBETON', 'ÇİMENTAŞ', 'ÇİMENTO', 'ÇİMSA', 'ÇİT', 'ÖMER',
            'ÖNENTAŞ', 'ÖZAK', 'ÖZBAL', 'ÖZDERİCİ', 'ÖZERDEN', 'ÖZİLHAN', 
            'ÜLKER', 'ÜNYE', 'ÜRETİM', 'ÜRÜNLER', 'ÜRÜNLERİ', 'ÜSTÜ',
            'İDARESİ', 'İDEALİST', 'İHLAS', 'İHRACAT', 'İLAÇ', 'İLAÇLARI', 'İLETİŞİM', 'İMALAT', 'İNDEKS', 'İNFO', 'İNTEGRE', 'İNTEMA', 'İNŞAAT',
            'İPEK', 'İPLİK', 'İSKENDERUN', 'İTHALAT', 'İTTİFAK', 'İZ', 'İZMİR', 'İZMİT', 'İZOCAM', 'İÇ', 'İÇECEK', 'İÇTAŞ', 'İŞ', 'İŞBİR', 'İŞLETME', 'İŞLETMECİLİK', 'İŞLETMECİLİĞİ', 'İŞLETMELERİ', 'İŞLETMESİ', 'İŞÇİ',
            'ŞEKER', 'ŞEKERBANK', 'ŞIRKETLER', 'ŞİRKETLER', 'ŞİRKETİ', 'ŞİŞE']

inFile = io.open(inFileName, 'r', encoding='utf-8')
lines = inFile.read().splitlines()

outFile = io.open(outFileName, 'w', encoding='utf-8')

# translation for Turksih 'İ', usage:
# string.translate(tr_map).upper()
tr_map = {
    ord(u'ı'): u'I',
    ord(u'i'): u'İ',
    }

for ln in lines:
    matches = re.finditer(regex, ln, re.MULTILINE | re.IGNORECASE)
    for matchNum, match in enumerate(matches):
        matchNum = matchNum + 1
        match = match.group()

        if match.translate(tr_map).upper() in orgWords:
            outFile.write(match + '\tI-ORG\n')
        else:
            outFile.write(match + '\tO\n')

    outFile.write('\n')



