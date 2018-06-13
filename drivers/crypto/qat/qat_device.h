/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2018 Intel Corporation
 */
#ifndef _QAT_DEVICE_H_
#define _QAT_DEVICE_H_

#include <rte_bus_pci.h>

#include "qat_common.h"
#include "qat_logs.h"
#include "adf_transport_access_macros.h"
#include "qat_qp.h"


#define QAT_DETACHED  (0)
#define QAT_ATTACHED  (1)

#define QAT_MAX_PCI_DEVICES	48
#define QAT_DEV_NAME_MAX_LEN	64

/*
 * This struct holds all the data about a QAT pci device
 * including data about all services it supports.
 * It contains
 *  - hw_data
 *  - config data
 *  - runtime data
 */
struct qat_sym_dev_private;
struct qat_pci_device {

	/* Data used by all services */
	char name[QAT_DEV_NAME_MAX_LEN];
	/**< Name of qat pci device */
	uint8_t qat_dev_id;
	/**< Device instance for this qat pci device */
	struct rte_pci_device *pci_dev;
	/**< PCI information. */
	enum qat_device_gen qat_dev_gen;
	/**< QAT device generation */
	rte_spinlock_t arb_csr_lock;
	/**< lock to protect accesses to the arbiter CSR */
	__extension__
	uint8_t attached : 1;
	/**< Flag indicating the device is attached */

	struct qat_qp *qps_in_use[QAT_MAX_SERVICES][ADF_MAX_QPS_ON_ANY_SERVICE];
	/**< links to qps set up for each service, index same as on API */

	/* Data relating to symmetric crypto service */
	struct qat_sym_dev_private *sym_dev;
	/**< link back to cryptodev private data */

	/* Data relating to compression service */

	/* Data relating to asymmetric crypto service */

};

struct qat_gen_hw_data {
	enum qat_device_gen dev_gen;
	const struct qat_qp_hw_data (*qp_hw_data)[ADF_MAX_QPS_ON_ANY_SERVICE];
};

extern struct qat_gen_hw_data qp_gen_config[];

struct qat_pci_device *
qat_pci_device_allocate(struct rte_pci_device *pci_dev);
int
qat_pci_device_release(struct rte_pci_device *pci_dev);
struct qat_pci_device *
qat_get_qat_dev_from_pci_dev(struct rte_pci_device *pci_dev);


#endif /* _QAT_DEVICE_H_ */